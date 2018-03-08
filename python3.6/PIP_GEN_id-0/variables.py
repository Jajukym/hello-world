#https://youtu.be/YXIlclFQZVU .whl install with pip install 'path to file and name of file'

mcu = ['PSOC', 'NRF51', 'RENESAS', 'XILOG'];

equipment = ['TREADMILL_DEVICE', 'INCLINE_TRAINER_DEVICE', 'ELLIPTICAL_DEVICE',
             'EXERCISE_BIKE_DEVICE', 'SPIN_BIKE_DEVICE', 'VERTICAL_ELLIPTICAL_DEVICE',
             'FITNESS_WT_MACH_DEVICE', 'FREE_STRIDER_DEVICE', 'ROWER_DEVICE'];

display = ['NO_DISPLAY', 'SISP_DISPLAY', 'AW_DISPLAY', 'AW_DESK', 'RICKENBACKER_DISPLAY',
           'RICKENBACKER_MINI_DISPLAY', 'PM210_DISPLAY_PAUL_REED_SMITH', 'PM210_DISPLAY_GIBSON_NORDIC',
           'POWER_RING_DISPLAY', 'POWER_RING_DISPLAY_LARGE', 'AERO_POWER_RING_DISPLAY','TTW_DISPLAY',
           'LED_900', 'CD_DISPLAY', 'FENDER_DISPLAY', 'OFENDER_DISPLAY', 'OP_DISPLAY', 'IF17_DISPLAY',
           'IF17_VERT_DISPLAY'];

tablet = ['RoyalWolf', 'Leagacy', 'Leagacy_FreeMotion']

controller = ['TREAD_TACH', 'MC1650LS_2W', 'MC1618DLS', 'MC1648DLS', 'MC1618DHB', 'MC1648DHB', 'MC1618IHS',#6
              'MC1648IHS', 'MC1618IHB', 'MC1648IHB', 'MC2100LT_12', 'MC2100LTS_30', 'MC2100LTS_50W', 'MC2100ELS_18W_2Y',#13
              'MC2100ELS_50W_2Y', 'MC5100DTS_18W', 'MC5100DTS_50W', 'MC5100DTS3_50W', 'MC5100EDS_50W_V1',#18
              'MC5100EDS3_50W_V1', 'MC5150HCL', 'OLYMPUS_V1', 'RHYMBUS_DOMESTIC', 'RHYMEBUS_EUROPEAN', 'BASIC_BIKE',#24
              'PB_INC_18W', 'PB_INC_50W', 'PB_INC_485_18W', 'PB_INC_485_50W', 'PB_PPI_485_18W', 'PB_PPI_485_48W',#30
              'PBCLA_2X50W_75W', 'PBCLA_FM_32_12V']; #Rhymebus not used in this

voltage = ['0', '6', '9', '12'];
resistance = ['ADC'];
distance = ['LoResTach'];

maintainance = ['CALIBRATE', 'TOGGLE_DISPLAY_ON_OFF', 'KEYCODE_TEST']; #tablet consoles will be different

keycode = ['SETTINGS', 'PRIORITY_DISPLAY', 'MANUAL']

ble = ['NO_PROFILE_SUPPORTED', 'WEIGHT_MACHINE_SUPPORTED', 'SPEED_RING_SUPPORTED', 'FILE_SYSTEM_SUPPORTED',
       'FITPRO_SYSTEM_SUPPORTED', 'HEART_RATE_SENSOR_SUPPORTED'];

pulse = ['Hand', 'Thumb', 'Chest', 'Ant', 'BLE', 'nanoHand', 'Priority'];

fan = ['TwoWire', 'ThreeWire', 'twoAndThree'];

audio = ['None', 'PC', 'BrainBoard', 'MP3', 'iPod', 'Headphones','BLE', 'TV', 'FM']; #audio functions

header = ['void for function call', 'RecordID', 'Link to Parts - Consoles', 'Link to Parts - Console Pics',
          'Part Number','Description', 'ProductType', 'Display Type', 'Equipment Needed', 'Setup', 'BLE SETUP',
          'Part Type Pull', 'PIP', 'Video of Inspection', 'EQF1259 Config', 'BLE Setup Image 1', 'BLE Setup Image 2',
          'Setup Image 1', 'Setup Image 2', 'ESD Bag', 'Cosmetics', 'Warning Label', 'Warning Label Picture',
          'Cosmetic, Color, and Texture', 'Picture of Console', 'Soldering Quality', 'Power up', 'Safety Key',
          'BLE Test', 'BLE Test Image 1', 'BLE Test Image 2', 'Software Version', 'Test Mode Image', 'Incline Calibration',
          'Display Test', 'Display Test Image', 'Button Test', 'Button Test Image', 'Drive Motor Output Test',
          'Tach Input Test', 'Resistance Motor Test', 'Incline Motor Test', 'USB port test', 'Hand Pulse Test',
          'Chest Pulse Test', 'Fan Test', 'Audio Test', 'TV Test', 'Upright Motor Test', 'Finish Test',
          'Last User', 'Created By User', 'Updated', 'Created'];