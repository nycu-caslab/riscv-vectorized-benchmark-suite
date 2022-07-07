# Copyright TU Wien
# Licensed under the Solderpad Hardware License v2.1, see LICENSE.txt for details
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1

    .text
    .global vmv_x_s_8
vmv_x_s_8:
    addi            sp, sp, -32
    sd              ra, 24(sp)
    sd              s0, 16(sp)
    addi            s0, sp,32

    li              t0, 16
    vsetvli         t0, t0, e8, m1, tu, mu

    vle8.v          v0, (a0)
    vmv.x.s         t1, v0
    mv              t3, t1

    li              t0, 4
    vsetvli         t0, t0, e32, m1, tu, mu

    vmv.v.x         v0, t1
    vse32.v         v0, (a0)
    mv              a0, t3

    ld              ra,24(sp)
    ld              s0,16(sp)
    addi            sp,sp,32
    jr              ra

    .text
    .global vmv_x_s_16
vmv_x_s_16:
    addi            sp, sp, -32
    sd              ra, 24(sp)
    sd              s0, 16(sp)
    addi            s0, sp,32

    li              t0, 8
    vsetvli         t0, t0, e16, m1, tu, mu

    vle16.v         v0, (a0)
    vmv.x.s         t1, v0
    mv              t3, t1

    li              t0, 4
    vsetvli         t0, t0, e32, m1, tu, mu

    vmv.v.x         v0, t1
    vse32.v         v0, (a0)
    mv              a0, t3

    ld              ra,24(sp)
    ld              s0,16(sp)
    addi            sp,sp,32
    jr              ra

    .text
    .global vmv_x_s_32
vmv_x_s_32:
    addi            sp, sp, -32
    sd              ra, 24(sp)
    sd              s0, 16(sp)
    addi            s0, sp,32

    li              t0, 4
    vsetvli         t0, t0, e32, m1, tu, mu

    vle32.v         v0, (a0)
    vmv.x.s         t0, v0
    mv              t3, t1

    vmv.v.x         v0, t0
    vse32.v         v0, (a0)
    mv              a0, t3

    ld              ra,24(sp)
    ld              s0,16(sp)
    addi            sp,sp,32
    jr              ra