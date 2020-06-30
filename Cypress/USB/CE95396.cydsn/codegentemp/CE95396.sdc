# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\bryan.lee\Documents\GitHub\hello-world\Cypress\USB\CE95396.cydsn\CE95396.cyprj
# Date: Fri, 03 Apr 2020 17:06:35 GMT
#set_units -time ns
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 15.625 -waveform {0 7.8125} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 15.625 -waveform {0 7.8125} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {ADC_SAR_1_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 41 81} [list [get_pins {ClockBlock/aclk_glb_0}]]
create_generated_clock -name {ADC_SAR_0_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 41 81} [list [get_pins {ClockBlock/aclk_glb_1}]]
create_generated_clock -name {Clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 65 129} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 7 11} -nominal_period 83.333333333333329 [list [get_pins {ClockBlock/dclk_glb_0}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\bryan.lee\Documents\GitHub\hello-world\Cypress\USB\CE95396.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\bryan.lee\Documents\GitHub\hello-world\Cypress\USB\CE95396.cydsn\CE95396.cyprj
# Date: Fri, 03 Apr 2020 17:06:23 GMT
