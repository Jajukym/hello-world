# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\bryan.lee\Desktop\PSoC-6-MCU-Pioneer-Kits-master\CY8CKIT-062-BLE Pioneer Kit\CE220167_BLE_UI\CE220167_BLE_UI.cydsn\CE220167_BLE_UI.cyprj
# Date: Fri, 08 Nov 2019 00:03:28 GMT
#set_units -time ns
create_clock -name {CyWCO} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyClk_LF} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyFLL} -period 20 -waveform {0 10} [list [get_pins {ClockBlock/fll}]]
create_clock -name {CyClk_HF0} -period 20 -waveform {0 10} [list [get_pins {ClockBlock/hfclk_0}]]
create_clock -name {CyClk_Fast} -period 20 -waveform {0 10} [list [get_pins {ClockBlock/fastclk}]]
create_clock -name {CyClk_Peri} -period 40 -waveform {0 20} [list [get_pins {ClockBlock/periclk}]]
create_generated_clock -name {CyClk_Slow} -source [get_pins {ClockBlock/periclk}] -edges {1 2 3} [list [get_pins {ClockBlock/slowclk}]]
create_generated_clock -name {CapSense_ModClk} -source [get_pins {ClockBlock/periclk}] -edges {1 255 511} [list [get_pins {ClockBlock/ff_div_43}]]
create_generated_clock -name {EINK_Clock} -source [get_pins {ClockBlock/periclk}] -edges {1 12501 25001} [list [get_pins {ClockBlock/ff_div_11}]]
create_generated_clock -name {Clock_Blue} -source [get_pins {ClockBlock/periclk}] -edges {1 13 25} [list [get_pins {ClockBlock/ff_div_12}]]
create_generated_clock -name {CY_EINK_SPIM_SCBCLK} -source [get_pins {ClockBlock/periclk}] -edges {1 2 3} [list [get_pins {ClockBlock/ff_div_6}]]
create_generated_clock -name {Clock_Red} -source [get_pins {ClockBlock/periclk}] -edges {1 13 25} [list [get_pins {ClockBlock/ff_div_20}]]
create_generated_clock -name {Clock_Green} -source [get_pins {ClockBlock/periclk}] -edges {1 13 25} [list [get_pins {ClockBlock/ff_div_22}]]
create_clock -name {CyPeriClk_App} -period 40 -waveform {0 20} [list [get_pins {ClockBlock/periclk_App}]]
create_clock -name {CyIMO} -period 125 -waveform {0 62.5} [list [get_pins {ClockBlock/imo}]]


# Component constraints for C:\Users\bryan.lee\Desktop\PSoC-6-MCU-Pioneer-Kits-master\CY8CKIT-062-BLE Pioneer Kit\CE220167_BLE_UI\CE220167_BLE_UI.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\bryan.lee\Desktop\PSoC-6-MCU-Pioneer-Kits-master\CY8CKIT-062-BLE Pioneer Kit\CE220167_BLE_UI\CE220167_BLE_UI.cydsn\CE220167_BLE_UI.cyprj
# Date: Fri, 08 Nov 2019 00:02:51 GMT
