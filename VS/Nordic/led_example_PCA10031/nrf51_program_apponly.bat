@echo off
@echo loadbin _build/blink_led.bin 0 > nrf51_program_app.jlink
@echo r >> nrf51_program_app.jlink
@echo g >> nrf51_program_app.jlink
@echo exit >> nrf51_program_app.jlink
JLink.exe -device nRF51422_xxAC -speed 4000 -commanderscript nrf51_program_app.jlink