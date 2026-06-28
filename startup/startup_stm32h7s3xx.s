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

.syntax unified
.cpu cortex-m7
.fpu softvfp
.thumb

.global vectors
.global default_handler

.word _siitcm
.word _sitcm
.word _eitcm
.word _sidtcm
.word _sdtcm
.word _edtcm
.word _sidata
.word _sdata
.word _edata
.word _sbss
.word _ebss


.section .text.reset_handler
.weak reset_handler
.type reset_handler, %function

reset_handler:
    ldr sp, = _estack

    ldr r0, = _sitcm
    ldr r1, = _eitcm
    ldr r2, = _siitcm
    movs r3, #0
    b loop_copy_itcm_init

copy_itcm_init:
    ldr r4, [r2, r3]
    str r4, [r0, r3]
    adds r3, r3, #4

loop_copy_itcm_init:
    adds r4, r0, r3
    cmp r4, r1
    bcc copy_itcm_init

    ldr r0, = _sdtcm
    ldr r1, = _edtcm
    ldr r2, = _sidtcm
    movs r3, #0
    b loop_copy_dtcm_init

copy_dtcm_init:
    ldr r4, [r2, r3]
    str r4, [r0, r3]
    adds r3, r3, #4

loop_copy_dtcm_init:
    adds r4, r0, r3
    cmp r4, r1
    bcc copy_dtcm_init

    ldr r0, = _sdata
    ldr r1, = _edata
    ldr r2, = _sidata
    movs r3, #0
    b loop_copy_data_init

copy_data_init:
    ldr r4, [r2, r3]
    str r4, [r0, r3]
    adds r3, r3, #4

loop_copy_data_init:
    adds r4, r0, r3
    cmp r4, r1
    bcc copy_data_init

    ldr r2, = _sbss
    ldr r4, = _ebss
    movs r3, #0
    b loop_fill_zero_bss

fill_zero_bss:
    str  r3, [r2]
    adds r2, r2, #4

loop_fill_zero_bss:
    cmp r2, r4
    bcc fill_zero_bss

    bl main
    bx lr

.size reset_handler, .-reset_handler


.section .text.default_handler, "ax", %progbits

default_handler:
    infinite_loop:
        b infinite_loop

.size default_handler, .-default_handler


.section .vectors, "a", %progbits
.type vectors, %object

vectors:
    .word _estack
    .word reset_handler

    .word nmi_handler
    .word hard_fault_handler
    .word mem_manage_handler
    .word bus_fault_handler
    .word usage_fault_handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word svc_handler
    .word debug_mon_handler
    .word 0
    .word pend_sv_handler
    .word systick_handler

    .word pvd_pvm_it_handler                 /* PVD/PVM through EXTI Line detection */
    .word 0                                  /* Reserved */
    .word dts_it_handler                     /* Digital Temperature Sensor */
    .word iwdg_it_handler                    /* Internal Watchdog */
    .word wwdg_it_handler                    /* Window Watchdog */
    .word rcc_it_handler                     /* RCC global interrupts through EXTI Line */
    .word 0                                  /* Reserved */
    .word 0                                  /* Reserved */
    .word flash_it_handler                   /* FLASH interrupts */
    .word ramecc_it_handler                  /* RAMECC interrupts */
    .word fpu_it_handler                     /* FPU */
    .word 0                                  /* Reserved */
    .word 0                                  /* Reserved */
    .word tamp_it_handler                    /* Tamper and TimeStamp interrupts */
    .word 0                                  /* Reserved */
    .word 0                                  /* Reserved */
    .word exti0_it_handler                   /* EXTI Line0 */
    .word exti1_it_handler                   /* EXTI Line1 */
    .word exti2_it_handler                   /* EXTI Line2 */
    .word exti3_it_handler                   /* EXTI Line3 */
    .word exti4_it_handler                   /* EXTI Line4 */
    .word exti5_it_handler                   /* EXTI Line5 */
    .word exti6_it_handler                   /* EXTI Line6 */
    .word exti7_it_handler                   /* EXTI Line7 */
    .word exti8_it_handler                   /* EXTI Line8 */
    .word exti9_it_handler                   /* EXTI Line9 */
    .word exti10_it_handler                  /* EXTI Line10 */
    .word exti11_it_handler                  /* EXTI Line11 */
    .word exti12_it_handler                  /* EXTI Line12 */
    .word exti13_it_handler                  /* EXTI Line13 */
    .word exti14_it_handler                  /* EXTI Line14 */
    .word exti15_it_handler                  /* EXTI Line15 */
    .word rtc_it_handler                     /* RTC wakeup and alarm interrupts */
    .word saes_it_handler                    /* SAES */
    .word cryp_it_handler                    /* CRYP */
    .word pka_it_handler                     /* PKA */
    .word hash_it_handler                    /* HASH */
    .word rng_it_handler                     /* RNG */
    .word adc1_2_it_handler                  /* ADC1 & ADC2 */
    .word gpdma1_channel0_it_handler         /* GPDMA1 Channel 0 */
    .word gpdma1_channel1_it_handler         /* GPDMA1 Channel 1 */
    .word gpdma1_channel2_it_handler         /* GPDMA1 Channel 2 */
    .word gpdma1_channel3_it_handler         /* GPDMA1 Channel 3 */
    .word gpdma1_channel4_it_handler         /* GPDMA1 Channel 4 */
    .word gpdma1_channel5_it_handler         /* GPDMA1 Channel 5 */
    .word gpdma1_channel6_it_handler         /* GPDMA1 Channel 6 */
    .word gpdma1_channel7_it_handler         /* GPDMA1 Channel 7 */
    .word tim1_brk_it_handler                /* TIM1 Break */
    .word tim1_up_it_handler                 /* TIM1 Update */
    .word tim1_trg_com_it_handler            /* TIM1 Trigger and Commutation */
    .word tim1_cc_it_handler                 /* TIM1 Capture Compare */
    .word tim2_it_handler                    /* TIM2 */
    .word tim3_it_handler                    /* TIM3 */
    .word tim4_it_handler                    /* TIM4 */
    .word tim5_it_handler                    /* TIM5 */
    .word tim6_it_handler                    /* TIM6 */
    .word tim7_it_handler                    /* TIM7 */
    .word tim9_it_handler                    /* TIM9 */
    .word spi1_it_handler                    /* SPI1 */
    .word spi2_it_handler                    /* SPI2 */
    .word spi3_it_handler                    /* SPI3 */
    .word spi4_it_handler                    /* SPI4 */
    .word spi5_it_handler                    /* SPI5 */
    .word spi6_it_handler                    /* SPI6 */
    .word hpdma1_channel0_it_handler         /* HPDMA1 Channel 0 */
    .word hpdma1_channel1_it_handler         /* HPDMA1 Channel 1 */
    .word hpdma1_channel2_it_handler         /* HPDMA1 Channel 2 */
    .word hpdma1_channel3_it_handler         /* HPDMA1 Channel 3 */
    .word hpdma1_channel4_it_handler         /* HPDMA1 Channel 4 */
    .word hpdma1_channel5_it_handler         /* HPDMA1 Channel 5 */
    .word hpdma1_channel6_it_handler         /* HPDMA1 Channel 6 */
    .word hpdma1_channel7_it_handler         /* HPDMA1 Channel 7 */
    .word sai1_a_it_handler                  /* SAI1 block A */
    .word sai1_b_it_handler                  /* SAI1 block B */
    .word sai2_a_it_handler                  /* SAI2 block A */
    .word sai2_b_it_handler                  /* SAI2 block B */
    .word i2c1_ev_it_handler                 /* I2C1 Event */
    .word i2c1_er_it_handler                 /* I2C1 Error */
    .word i2c2_ev_it_handler                 /* I2C2 Event */
    .word i2c2_er_it_handler                 /* I2C2 Error */
    .word i2c3_ev_it_handler                 /* I2C3 Event */
    .word i2c3_er_it_handler                 /* I2C3 Error */
    .word usart1_it_handler                  /* USART1 */
    .word usart2_it_handler                  /* USART2 */
    .word usart3_it_handler                  /* USART3 */
    .word uart4_it_handler                   /* UART4 */
    .word uart5_it_handler                   /* UART5 */
    .word uart7_it_handler                   /* UART7 */
    .word uart8_it_handler                   /* UART8 */
    .word i3c1_ev_it_handler                 /* I3C1 Event */
    .word i3c1_er_it_handler                 /* I3C1 Error */
    .word otg_hs_it_handler                  /* USB OTG HS */
    .word eth_it_handler                     /* Ethernet */
    .word cordic_it_handler                  /* CORDIC */
    .word gfxtim_it_handler                  /* GFXTIM */
    .word dcmipp_it_handler                  /* DCMIPP */
    .word 0                                  /* Reserved */
    .word 0                                  /* Reserved */
    .word dma2d_it_handler                   /* DMA2D */
    .word jpeg_it_handler                    /* JPEG */
    .word gfxmmu_it_handler                  /* GFXMMU */
    .word i3c1_wkup_it_handler               /* I3C1 wakeup */
    .word mce1_it_handler                    /* MCE1 */
    .word mce2_it_handler                    /* MCE2 */
    .word mce3_it_handler                    /* MCE3 */
    .word xspi1_it_handler                   /* XSPI1 */
    .word xspi2_it_handler                   /* XSPI2 */
    .word fmc_it_handler                     /* FMC */
    .word sdmmc1_it_handler                  /* SDMMC1 */
    .word sdmmc2_it_handler                  /* SDMMC2 */
    .word 0                                  /* Reserved */
    .word 0                                  /* Reserved */
    .word otg_fs_it_handler                  /* USB OTG FS */
    .word tim12_it_handler                   /* TIM12 */
    .word tim13_it_handler                   /* TIM13 */
    .word tim14_it_handler                   /* TIM14 */
    .word tim15_it_handler                   /* TIM15 */
    .word tim16_it_handler                   /* TIM16 */
    .word tim17_it_handler                   /* TIM17 */
    .word lptim1_it_handler                  /* LPTIM1 */
    .word lptim2_it_handler                  /* LPTIM2 */
    .word lptim3_it_handler                  /* LPTIM3 */
    .word lptim4_it_handler                  /* LPTIM4 */
    .word lptim5_it_handler                  /* LPTIM5 */
    .word spdif_rx_it_handler                /* SPDIF_RX */
    .word mdios_it_handler                   /* MDIOS */
    .word adf1_flt0_it_handler               /* ADF1 Filter 0 */
    .word crs_it_handler                     /* CRS */
    .word ucpd1_it_handler                   /* UCPD1 */
    .word cec_it_handler                     /* HDMI-CEC */
    .word pssi_it_handler                    /* PSSI */
    .word lpuart1_it_handler                 /* LPUART1 */
    .word wakeup_pin_it_handler              /* Wake-up pins interrupt */
    .word gpdma1_channel8_it_handler         /* GPDMA1 Channel 8 */
    .word gpdma1_channel9_it_handler         /* GPDMA1 Channel 9 */
    .word gpdma1_channel10_it_handler        /* GPDMA1 Channel 10 */
    .word gpdma1_channel11_it_handler        /* GPDMA1 Channel 11 */
    .word gpdma1_channel12_it_handler        /* GPDMA1 Channel 12 */
    .word gpdma1_channel13_it_handler        /* GPDMA1 Channel 13 */
    .word gpdma1_channel14_it_handler        /* GPDMA1 Channel 14 */
    .word gpdma1_channel15_it_handler        /* GPDMA1 Channel 15 */
    .word hpdma1_channel8_it_handler         /* HPDMA1 Channel 8 */
    .word hpdma1_channel9_it_handler         /* HPDMA1 Channel 9 */
    .word hpdma1_channel10_it_handler        /* HPDMA1 Channel 10 */
    .word hpdma1_channel11_it_handler        /* HPDMA1 Channel 11 */
    .word hpdma1_channel12_it_handler        /* HPDMA1 Channel 12 */
    .word hpdma1_channel13_it_handler        /* HPDMA1 Channel 13 */
    .word hpdma1_channel14_it_handler        /* HPDMA1 Channel 14 */
    .word hpdma1_channel15_it_handler        /* HPDMA1 Channel 15 */
    .word 0                                  /* Reserved */
    .word 0                                  /* Reserved */
    .word 0                                  /* Reserved */
    .word fdcan1_it0_it_handler              /* FDCAN1 Interrupt 0 */
    .word fdcan1_it1_it_handler              /* FDCAN1 Interrupt 1 */
    .word fdcan2_it0_it_handler              /* FDCAN2 Interrupt 0 */
    .word fdcan2_it1_it_handler              /* FDCAN2 Interrupt 1 */

.size vectors, .-vectors


.weak      nmi_handler
.thumb_set nmi_handler, default_handler

.weak      hard_fault_handler
.thumb_set hard_fault_handler, default_handler

.weak      mem_manage_handler
.thumb_set mem_manage_handler, default_handler

.weak      bus_fault_handler
.thumb_set bus_fault_handler, default_handler

.weak      usage_fault_handler
.thumb_set usage_fault_handler, default_handler

.weak      svc_handler
.thumb_set svc_handler, default_handler

.weak      debug_mon_handler
.thumb_set debug_mon_handler, default_handler

.weak      pend_sv_handler
.thumb_set pend_sv_handler, default_handler

.weak      systick_handler
.thumb_set systick_handler, default_handler

.weak      pvd_pvm_it_handler
.thumb_set pvd_pvm_it_handler, default_handler

.weak      dts_it_handler
.thumb_set dts_it_handler, default_handler

.weak      iwdg_it_handler
.thumb_set iwdg_it_handler, default_handler

.weak      wwdg_it_handler
.thumb_set wwdg_it_handler, default_handler

.weak      rcc_it_handler
.thumb_set rcc_it_handler, default_handler

.weak      flash_it_handler
.thumb_set flash_it_handler, default_handler

.weak      ramecc_it_handler
.thumb_set ramecc_it_handler, default_handler

.weak      fpu_it_handler
.thumb_set fpu_it_handler, default_handler

.weak      tamp_it_handler
.thumb_set tamp_it_handler, default_handler

.weak      exti0_it_handler
.thumb_set exti0_it_handler, default_handler

.weak      exti1_it_handler
.thumb_set exti1_it_handler, default_handler

.weak      exti2_it_handler
.thumb_set exti2_it_handler, default_handler

.weak      exti3_it_handler
.thumb_set exti3_it_handler, default_handler

.weak      exti4_it_handler
.thumb_set exti4_it_handler, default_handler

.weak      exti5_it_handler
.thumb_set exti5_it_handler, default_handler

.weak      exti6_it_handler
.thumb_set exti6_it_handler, default_handler

.weak      exti7_it_handler
.thumb_set exti7_it_handler, default_handler

.weak      exti8_it_handler
.thumb_set exti8_it_handler, default_handler

.weak      exti9_it_handler
.thumb_set exti9_it_handler, default_handler

.weak      exti10_it_handler
.thumb_set exti10_it_handler, default_handler

.weak      exti11_it_handler
.thumb_set exti11_it_handler, default_handler

.weak      exti12_it_handler
.thumb_set exti12_it_handler, default_handler

.weak      exti13_it_handler
.thumb_set exti13_it_handler, default_handler

.weak      exti14_it_handler
.thumb_set exti14_it_handler, default_handler

.weak      exti15_it_handler
.thumb_set exti15_it_handler, default_handler

.weak      rtc_it_handler
.thumb_set rtc_it_handler, default_handler

.weak      saes_it_handler
.thumb_set saes_it_handler, default_handler

.weak      cryp_it_handler
.thumb_set cryp_it_handler, default_handler

.weak      pka_it_handler
.thumb_set pka_it_handler, default_handler

.weak      hash_it_handler
.thumb_set hash_it_handler, default_handler

.weak      rng_it_handler
.thumb_set rng_it_handler, default_handler

.weak      adc1_2_it_handler
.thumb_set adc1_2_it_handler, default_handler

.weak      gpdma1_channel0_it_handler
.thumb_set gpdma1_channel0_it_handler, default_handler

.weak      gpdma1_channel1_it_handler
.thumb_set gpdma1_channel1_it_handler, default_handler

.weak      gpdma1_channel2_it_handler
.thumb_set gpdma1_channel2_it_handler, default_handler

.weak      gpdma1_channel3_it_handler
.thumb_set gpdma1_channel3_it_handler, default_handler

.weak      gpdma1_channel4_it_handler
.thumb_set gpdma1_channel4_it_handler, default_handler

.weak      gpdma1_channel5_it_handler
.thumb_set gpdma1_channel5_it_handler, default_handler

.weak      gpdma1_channel6_it_handler
.thumb_set gpdma1_channel6_it_handler, default_handler

.weak      gpdma1_channel7_it_handler
.thumb_set gpdma1_channel7_it_handler, default_handler

.weak      tim1_brk_it_handler
.thumb_set tim1_brk_it_handler, default_handler

.weak      tim1_up_it_handler
.thumb_set tim1_up_it_handler, default_handler

.weak      tim1_trg_com_it_handler
.thumb_set tim1_trg_com_it_handler, default_handler

.weak      tim1_cc_it_handler
.thumb_set tim1_cc_it_handler, default_handler

.weak      tim2_it_handler
.thumb_set tim2_it_handler, default_handler

.weak      tim3_it_handler
.thumb_set tim3_it_handler, default_handler

.weak      tim4_it_handler
.thumb_set tim4_it_handler, default_handler

.weak      tim5_it_handler
.thumb_set tim5_it_handler, default_handler

.weak      tim6_it_handler
.thumb_set tim6_it_handler, default_handler

.weak      tim7_it_handler
.thumb_set tim7_it_handler, default_handler

.weak      tim9_it_handler
.thumb_set tim9_it_handler, default_handler

.weak      spi1_it_handler
.thumb_set spi1_it_handler, default_handler

.weak      spi2_it_handler
.thumb_set spi2_it_handler, default_handler

.weak      spi3_it_handler
.thumb_set spi3_it_handler, default_handler

.weak      spi4_it_handler
.thumb_set spi4_it_handler, default_handler

.weak      spi5_it_handler
.thumb_set spi5_it_handler, default_handler

.weak      spi6_it_handler
.thumb_set spi6_it_handler, default_handler

.weak      hpdma1_channel0_it_handler
.thumb_set hpdma1_channel0_it_handler, default_handler

.weak      hpdma1_channel1_it_handler
.thumb_set hpdma1_channel1_it_handler, default_handler

.weak      hpdma1_channel2_it_handler
.thumb_set hpdma1_channel2_it_handler, default_handler

.weak      hpdma1_channel3_it_handler
.thumb_set hpdma1_channel3_it_handler, default_handler

.weak      hpdma1_channel4_it_handler
.thumb_set hpdma1_channel4_it_handler, default_handler

.weak      hpdma1_channel5_it_handler
.thumb_set hpdma1_channel5_it_handler, default_handler

.weak      hpdma1_channel6_it_handler
.thumb_set hpdma1_channel6_it_handler, default_handler

.weak      hpdma1_channel7_it_handler
.thumb_set hpdma1_channel7_it_handler, default_handler

.weak      sai1_a_it_handler
.thumb_set sai1_a_it_handler, default_handler

.weak      sai1_b_it_handler
.thumb_set sai1_b_it_handler, default_handler

.weak      sai2_a_it_handler
.thumb_set sai2_a_it_handler, default_handler

.weak      sai2_b_it_handler
.thumb_set sai2_b_it_handler, default_handler

.weak      i2c1_ev_it_handler
.thumb_set i2c1_ev_it_handler, default_handler

.weak      i2c1_er_it_handler
.thumb_set i2c1_er_it_handler, default_handler

.weak      i2c2_ev_it_handler
.thumb_set i2c2_ev_it_handler, default_handler

.weak      i2c2_er_it_handler
.thumb_set i2c2_er_it_handler, default_handler

.weak      i2c3_ev_it_handler
.thumb_set i2c3_ev_it_handler, default_handler

.weak      i2c3_er_it_handler
.thumb_set i2c3_er_it_handler, default_handler

.weak      usart1_it_handler
.thumb_set usart1_it_handler, default_handler

.weak      usart2_it_handler
.thumb_set usart2_it_handler, default_handler

.weak      usart3_it_handler
.thumb_set usart3_it_handler, default_handler

.weak      uart4_it_handler
.thumb_set uart4_it_handler, default_handler

.weak      uart5_it_handler
.thumb_set uart5_it_handler, default_handler

.weak      uart7_it_handler
.thumb_set uart7_it_handler, default_handler

.weak      uart8_it_handler
.thumb_set uart8_it_handler, default_handler

.weak      i3c1_ev_it_handler
.thumb_set i3c1_ev_it_handler, default_handler

.weak      i3c1_er_it_handler
.thumb_set i3c1_er_it_handler, default_handler

.weak      otg_hs_it_handler
.thumb_set otg_hs_it_handler, default_handler

.weak      eth_it_handler
.thumb_set eth_it_handler, default_handler

.weak      cordic_it_handler
.thumb_set cordic_it_handler, default_handler

.weak      gfxtim_it_handler
.thumb_set gfxtim_it_handler, default_handler

.weak      dcmipp_it_handler
.thumb_set dcmipp_it_handler, default_handler

.weak      dma2d_it_handler
.thumb_set dma2d_it_handler, default_handler

.weak      jpeg_it_handler
.thumb_set jpeg_it_handler, default_handler

.weak      gfxmmu_it_handler
.thumb_set gfxmmu_it_handler, default_handler

.weak      i3c1_wkup_it_handler
.thumb_set i3c1_wkup_it_handler, default_handler

.weak      mce1_it_handler
.thumb_set mce1_it_handler, default_handler

.weak      mce2_it_handler
.thumb_set mce2_it_handler, default_handler

.weak      mce3_it_handler
.thumb_set mce3_it_handler, default_handler

.weak      xspi1_it_handler
.thumb_set xspi1_it_handler, default_handler

.weak      xspi2_it_handler
.thumb_set xspi2_it_handler, default_handler

.weak      fmc_it_handler
.thumb_set fmc_it_handler, default_handler

.weak      sdmmc1_it_handler
.thumb_set sdmmc1_it_handler, default_handler

.weak      sdmmc2_it_handler
.thumb_set sdmmc2_it_handler, default_handler

.weak      otg_fs_it_handler
.thumb_set otg_fs_it_handler, default_handler

.weak      tim12_it_handler
.thumb_set tim12_it_handler, default_handler

.weak      tim13_it_handler
.thumb_set tim13_it_handler, default_handler

.weak      tim14_it_handler
.thumb_set tim14_it_handler, default_handler

.weak      tim15_it_handler
.thumb_set tim15_it_handler, default_handler

.weak      tim16_it_handler
.thumb_set tim16_it_handler, default_handler

.weak      tim17_it_handler
.thumb_set tim17_it_handler, default_handler

.weak      lptim1_it_handler
.thumb_set lptim1_it_handler, default_handler

.weak      lptim2_it_handler
.thumb_set lptim2_it_handler, default_handler

.weak      lptim3_it_handler
.thumb_set lptim3_it_handler, default_handler

.weak      lptim4_it_handler
.thumb_set lptim4_it_handler, default_handler

.weak      lptim5_it_handler
.thumb_set lptim5_it_handler, default_handler

.weak      spdif_rx_it_handler
.thumb_set spdif_rx_it_handler, default_handler

.weak      mdios_it_handler
.thumb_set mdios_it_handler, default_handler

.weak      adf1_flt0_it_handler
.thumb_set adf1_flt0_it_handler, default_handler

.weak      crs_it_handler
.thumb_set crs_it_handler, default_handler

.weak      ucpd1_it_handler
.thumb_set ucpd1_it_handler, default_handler

.weak      cec_it_handler
.thumb_set cec_it_handler, default_handler

.weak      pssi_it_handler
.thumb_set pssi_it_handler, default_handler

.weak      lpuart1_it_handler
.thumb_set lpuart1_it_handler, default_handler

.weak      wakeup_pin_it_handler
.thumb_set wakeup_pin_it_handler, default_handler

.weak      gpdma1_channel8_it_handler
.thumb_set gpdma1_channel8_it_handler, default_handler

.weak      gpdma1_channel9_it_handler
.thumb_set gpdma1_channel9_it_handler, default_handler

.weak      gpdma1_channel10_it_handler
.thumb_set gpdma1_channel10_it_handler, default_handler

.weak      gpdma1_channel11_it_handler
.thumb_set gpdma1_channel11_it_handler, default_handler

.weak      gpdma1_channel12_it_handler
.thumb_set gpdma1_channel12_it_handler, default_handler

.weak      gpdma1_channel13_it_handler
.thumb_set gpdma1_channel13_it_handler, default_handler

.weak      gpdma1_channel14_it_handler
.thumb_set gpdma1_channel14_it_handler, default_handler

.weak      gpdma1_channel15_it_handler
.thumb_set gpdma1_channel15_it_handler, default_handler

.weak      hpdma1_channel8_it_handler
.thumb_set hpdma1_channel8_it_handler, default_handler

.weak      hpdma1_channel9_it_handler
.thumb_set hpdma1_channel9_it_handler, default_handler

.weak      hpdma1_channel10_it_handler
.thumb_set hpdma1_channel10_it_handler, default_handler

.weak      hpdma1_channel11_it_handler
.thumb_set hpdma1_channel11_it_handler, default_handler

.weak      hpdma1_channel12_it_handler
.thumb_set hpdma1_channel12_it_handler, default_handler

.weak      hpdma1_channel13_it_handler
.thumb_set hpdma1_channel13_it_handler, default_handler

.weak      hpdma1_channel14_it_handler
.thumb_set hpdma1_channel14_it_handler, default_handler

.weak      hpdma1_channel15_it_handler
.thumb_set hpdma1_channel15_it_handler, default_handler

.weak      fdcan1_it0_it_handler
.thumb_set fdcan1_it0_it_handler, default_handler

.weak      fdcan1_it1_it_handler
.thumb_set fdcan1_it1_it_handler, default_handler

.weak      fdcan2_it0_it_handler
.thumb_set fdcan2_it0_it_handler, default_handler

.weak      fdcan2_it1_it_handler
.thumb_set fdcan2_it1_it_handler, default_handler
