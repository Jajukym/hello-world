# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\bryan.lee\Documents\GitHub\hello-world\Psoc_102_4BLE\PSoC_101\Design02.cydsn\Design02.cyprj
# Date: Sat, 19 Oct 2019 23:04:56 GMT
#set_units -time ns
create_clock -name {CapSense_SampleClk(FFB)} -period 5312.5 -waveform {0 2656.25} [list [get_pins {ClockBlock/ff_div_5}]]
create_clock -name {CapSense_SenseClk(FFB)} -period 5312.5 -waveform {0 2656.25} [list [get_pins {ClockBlock/ff_div_4}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyWCO} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyLFClk} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyECO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/eco}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {CapSense_SampleClk} -source [get_pins {ClockBlock/hfclk}] -edges {1 255 511} [list]
create_generated_clock -name {CapSense_SenseClk} -source [get_pins {ClockBlock/hfclk}] -edges {1 255 511} [list]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\bryan.lee\Documents\GitHub\hello-world\Psoc_102_4BLE\PSoC_101\Design02.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\bryan.lee\Documents\GitHub\hello-world\Psoc_102_4BLE\PSoC_101\Design02.cydsn\Design02.cyprj
# Date: Sat, 19 Oct 2019 23:04:51 GMT
