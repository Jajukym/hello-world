/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
int capsenseNotify;
int bleConnected = 0;

CYBLE_CONN_HANDLE_T connectionHandle;

void Stack_Handler(uint32 eventCode, void *eventParam)
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReq;
    
    switch(eventCode)
    {
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            bleConnected = 0;
            break;
        
        case CYBLE_EVT_GATT_CONNECT_IND:
            connectionHandle = *(CYBLE_CONN_HANDLE_T *)eventParam;
            bleConnected = 1;
            break;
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReq = (CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam;
            if(wrReq->handleValPair.attrHandle == CYBLE_CAPSENSE_SLIDER_SLIDERCCCD_DESC_HANDLE)
            {
                CyBle_GattsWriteAttributeValue(&wrReq->handleValPair, 0, &connectionHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                capsenseNotify = wrReq->handleValPair.value.val [0];
            }
            CyBle_GattsWriteRsp(connectionHandle);
            break;
            
            default:
            break;
    }
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    CapSense_ScanEnabledWidgets();
    
    CyBle_Start(Stack_Handler);

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        CyBle_ProcessEvents();
        
        if(!CapSense_IsBusy() && bleConnected)
        {
            uint8 pos = (uint8)CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);
            
            CapSense_UpdateEnabledBaselines();
            CapSense_ScanEnabledWidgets();
            
            if(pos != 0xFF)
            {
                CYBLE_GATTS_HANDLE_VALUE_IND_T capsenseHandle;
                
                capsenseHandle.attrHandle = CYBLE_CAPSENSE_SLIDER_CHAR_HANDLE;
                capsenseHandle.value.val = &pos;
                capsenseHandle.value.len = 1;
                
                CyBle_GattsWriteAttributeValue(&capsenseHandle, 0, &connectionHandle, 0);
                
                if(capsenseNotify)
                    CyBle_GattsNotification(connectionHandle, &capsenseHandle);
            }
        }
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
