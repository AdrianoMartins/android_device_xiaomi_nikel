/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */

#ifndef __FMR_H__
#define __FMR_H__

#include <jni.h>
#include <utils/Log.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <pthread.h>
#include <linux/serial.h>
//#include <linux/fm.h>
#include <signal.h>
#include <errno.h>
#include <dlfcn.h>
#include "../custom/fmlib_cust.h"
#include <system/radio.h>
#include "fm.h"

#undef LOGV
#define LOGV(...) ALOGV(__VA_ARGS__)
#undef LOGD
#define LOGD(...) ALOGD(__VA_ARGS__)
#undef LOGI
#define LOGI(...) ALOGI(__VA_ARGS__)
#undef LOGW
#define LOGW(...) ALOGW(__VA_ARGS__)
#undef LOGE
#define LOGE(...) ALOGE(__VA_ARGS__)

#define CUST_LIB_NAME "libfmcust.so"
#define FM_DEV_NAME "/dev/fm"

#define FM_RDS_PS_LEN 8

typedef int (*CUST_func_type)(struct CUST_cfg_ds *);
//typedef void (*init_func_type)(struct fm_cbk_tbl *);

struct fmr_ds {
    int fd;
    int err;
    uint16_t cur_freq;
    uint16_t backup_freq;
    void *priv;
    void *custom_handler;
    struct CUST_cfg_ds cfg_data;
    //struct fm_cbk_tbl tbl;
    CUST_func_type get_cfg;
    void *init_handler;
    //init_func_type init_func;
    RDSData_Struct rds;
    struct fm_hw_info hw_info;
    fm_bool scan_stop;
};

enum fmr_err_em {
    ERR_SUCCESS = 1000, // kernel error begin at here
    ERR_INVALID_BUF,
    ERR_INVALID_PARA,
    ERR_STP,
    ERR_GET_MUTEX,
    ERR_FW_NORES,
    ERR_RDS_CRC,
    ERR_INVALID_FD, //  native error begin at here
    ERR_UNSUPPORT_CHIP,
    ERR_LD_LIB,
    ERR_FIND_CUST_FNUC,
    ERR_UNINIT,
    ERR_NO_MORE_IDX,
    ERR_RDS_NO_DATA,
    ERR_UNSUPT_SHORTANA,
    ERR_MAX
};

enum fmr_rds_onoff {
    FMR_RDS_ON,
    FMR_RDS_OFF,
    FMR_MAX
};

typedef enum {
    FM_LONG_ANA = 0,
    FM_SHORT_ANA
}fm_antenna_type;


#define CQI_CH_NUM_MAX 255
#define CQI_CH_NUM_MIN 0


/****************** Function declaration ******************/
//fmr_err.cpp
char *FMR_strerr();
void FMR_seterr(int err);

//fmr_core.cpp
int FMR_init(void);
int FMR_get_cfgs(void);
int FMR_open_dev(int *idx);
int FMR_close_dev(int idx);
int FMR_pwr_up(int idx, const radio_hal_band_config_t *config);
int FMR_pwr_down(int idx, int type);
int FMR_seek(int idx, radio_hal_band_config_t *config, unsigned int start_freq, unsigned int dir, radio_program_info_t *ret_info);
int FMR_stop_scan(void);
int FMR_tune(int idx, unsigned int freq);
int FMR_set_mute(int idx, int mute);
int FMR_is_fm_pwrup(int idx, int *pwrup);
int FM_set_status(int idx, int which, bool stat);
int FM_get_status(int idx, int which, bool *stat);
int FMR_is_rdsrx_support(int idx, int *supt);
int FMR_turn_on_off_rds(int idx, int onoff);
int FMR_get_chip_id(int idx, int *chipid);
int FMR_read_rds_data(int idx, uint16_t *rds_status);
int FMR_get_pi(uint16_t *pi);
int FMR_get_ps(uint8_t **ps, int *ps_len);
int FMR_get_pty(uint8_t *pty);
int FMR_get_rssi(int idx, int *rssi);
int FMR_get_rt(uint8_t **rt, int *rt_len);
int FMR_active_af(int idx, uint16_t *ret_freq);
int FMR_active_ta(int idx, uint16_t *ret_freq);
int FMR_deactive_ta(int idx, uint16_t *ret_freq);
int FMR_ana_switch(int idx, int antenna);
int FMR_get_badratio(int idx, int *badratio);
int FMR_get_stereomono(int idx, int *stemono);
int FMR_set_stereomono(int idx, int stemono);
int FMR_get_caparray(int idx, int *caparray);
int FMR_get_hw_info(int idx, int **info, int *info_len);
int FMR_Pre_Search(int idx);
int FMR_Restore_Search(int idx);
int FMR_EMSetTH(int idx, int th_idx, int th_val);
int FMR_EM_CQI_logger(int idx,uint16_t cycle);

//common part
int COM_open_dev(const char *pname, int *fd);
int COM_close_dev(int fd);
int COM_pwr_up(int fd, int band, int freq);
int COM_pwr_down(int fd, int type);
int COM_seek(int fd, int *freq, int band, int dir, int lev);
int COM_Soft_Mute_Tune(int fd, struct fm_softmute_tune_t * para);
int COM_fastget_rssi(int fd, struct fm_rssi_req *rssi_req);
int COM_get_cqi(int fd, int num, char *buf, int buf_len);
int COM_sw_scan(int fd, uint16_t *tbl, int *num, int band);
int COM_stop_scan(void);
int COM_tune(int fd, int freq);
int COM_set_mute(int fd, int mute);
int COM_is_fm_pwrup(int fd, int *pwrup);
int COM_fm_set_status(int fd, int which, bool stat);
int COM_fm_get_status(int fd, int which, bool *stat);
int COM_turn_on_off_rds(int fd, int onoff);
int COM_is_rdsrx_support(int fd, int *supt);
int COM_get_chip_id(int fd, int *chipid);
int COM_read_rds_data(int fd, RDSData_Struct *rds, uint16_t *rds_status);
int COM_get_pi(RDSData_Struct *rds, uint16_t *pi);
int COM_get_ps(RDSData_Struct *rds, uint8_t **ps, int *ps_len);
int COM_get_pty(RDSData_Struct *rds, uint8_t *pty);
int COM_get_rssi(int fd, int *rssi);
int COM_get_rt(RDSData_Struct *rds, uint8_t **rt, int *rt_len);
int COM_active_af(int fd, RDSData_Struct *rds, int band, uint16_t cur_freq, uint16_t *ret_freq);
int COM_active_ta(int fd, RDSData_Struct *rds, int band, uint16_t cur_freq, uint16_t *backup_freq, uint16_t *ret_freq);
int COM_deactive_ta(int fd, RDSData_Struct *rds, uint16_t cur_freq, uint16_t *backup_freq, uint16_t *ret_freq);
int COM_ana_switch(int fd, int antenna);
int COM_get_badratio(int fd, int *badratio);
int COM_get_stereomono(int fd, int *stemono);
int COM_set_stereomono(int fd, int stemono);
int COM_get_caparray(int fd, int *caparray);
int COM_get_hw_info(int fd, struct fm_hw_info *info);
int COM_is_dese_chan(int fd, int freq);
int COM_desense_check(int fd, int freq, int rssi);
int COM_pre_search(int fd);
int COM_restore_search(int fd);
int COM_set_search_threshold(int fd, int th_idx,int th_val);
int COM_full_cqi_logger(int fd, fm_full_cqi_log_t *log_parm);


#define FMR_ASSERT(a) { \
            if ((a) == NULL) { \
                LOGE("%s,invalid buf\n", __func__);\
                return -ERR_INVALID_BUF; \
            } \
        }
#endif
