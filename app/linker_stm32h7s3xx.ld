/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

ENTRY(reset_handler)

MEMORY 
{
    FLASH       (rx)  : ORIGIN = 0x70000000, LENGTH = 32M   /* External flash */
    ITCM        (xrw) : ORIGIN = 0x00000000, LENGTH = 128K  /* ITCM */
    DTCM        (xrw) : ORIGIN = 0x20000000, LENGTH = 128K  /* DTCM */
    AXISRAM     (xrw) : ORIGIN = 0x24010000, LENGTH = 328K  /* AXI SRAM */
    SRAM1       (xrw) : ORIGIN = 0x30000000, LENGTH = 16K   /* SRAM1 (AHB domain) */
    SRAM2       (xrw) : ORIGIN = 0x30004000, LENGTH = 16K   /* SRAM2 (AHB domain) */
    BKPSRAM     (xrw) : ORIGIN = 0x38800000, LENGTH = 4K    /* Backup SRAM (AHB domain) */
}

SECTIONS
{
    .vectors : 
    {
        . = ALIGN(4);
        KEEP(*(.vectors))
        . = ALIGN(4);
    } >FLASH

    .text : 
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        . = ALIGN(4);
        _etext = .;
    } >FLASH

    .rodata : 
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } >FLASH

    .itcm_code : 
    {
        . = ALIGN(4);
        _sitcm = .;
        *(.itcm_code)
        *(.itcm_code*)
        . = ALIGN(4);
        _eitcm = .;
    } >ITCM AT> FLASH
    _siitcm = LOADADDR(.itcm_code);
    
    .dtcm_data : 
    {
        . = ALIGN(4);
        _sdtcm = .;
        *(.dtcm_data)
        *(.dtcm_data*)
        . = ALIGN(4);
        _edtcm = .;
    } >DTCM AT> FLASH
    _sidtcm = LOADADDR(.dtcm_data);
    
    .data : 
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } >AXISRAM AT> FLASH
	_sidata = LOADADDR(.data);
	
    .bss (NOLOAD): 
    {
    	. = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >AXISRAM

    .stack (NOLOAD): 
    {
        . = ALIGN(8);
        _sstack = .;
        PROVIDE(end = .);
        PROVIDE(_end = .);
        . = . + 4K;
        . = ALIGN(8);
        _estack = .;
    } >DTCM
    
    ASSERT(_estack <= ORIGIN(DTCM) + LENGTH(DTCM), "DTCM overflowed!")
}