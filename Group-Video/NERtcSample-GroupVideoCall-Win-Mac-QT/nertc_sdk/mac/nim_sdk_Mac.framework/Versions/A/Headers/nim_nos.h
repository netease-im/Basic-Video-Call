/** @file nim_nos.h
  * @brief NOS云存储服务 接口头文件
  * @copyright (c) 2015-2017, NetEase Inc. All rights reserved
  * @author Oleg
  * @date 2015/2/1
  */
#ifndef NIM_SDK_DLL_API_NIM_NOS_H_
#define NIM_SDK_DLL_API_NIM_NOS_H_

#include "public_define/defines/nim_sdk_dll.h"
#include "public_define/defines/nim_define/nim_nos_def.h"

#ifdef __cplusplus
extern"C"
{
#endif

/** @fn void nim_nos_init_config(const char* json_tags, nim_nos_init_config_cb_func cb,const char *json_extension, const void *user_data)
* SDK Nos模块初始化接口，对上传资源时使用的各场景资源生命周期进行初始化，开发者最多可自定义10个场景，并指定场景资源的生命周期，并可以对缺省场景（kNIMNosDefaultTagResource、kNIMNosDefaultTagIM）进行覆盖（重新指定生命周期）
* @param[in] json_tags 要进行设定的tag信息，json格式
* @param[in] cb 结果回调函数， nim_nos_init_config_cb_func回调函数定义见nim_nos_def.h
* @param[in] json_extension json扩展参数
* @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
* @return void 无返回值
*/
NIM_SDK_DLL_API void nim_nos_init_config(const char* json_tags, nim_nos_init_config_cb_func cb, const char *json_extension, const void *user_data);

/** @fn void nim_nos_reg_download_cb(nim_nos_download_cb_func cb, const void *user_data)
  * (全局回调)注册下载回调，通过注册回调获得HTTP下载结果通知（所有触发HTTP下载任务的接口的参数列表里无法设置通知回调处理函数的通知都走这个通知，比如收到图片语音会触发SDK自动下载等，开发者可以通过监听这个广播通知结果刷新UI资源）
  * @param[in] cb 下载的回调函数， nim_nos_download_cb_func回调函数定义见nim_nos_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_nos_reg_download_cb(nim_nos_download_cb_func cb, const void *user_data);

/** @fn void nim_nos_reg_upload_cb(nim_nos_upload_cb_func cb, const void *user_data)
  * (全局回调)注册上传回调，通过注册回调获得HTTP上传结果通知（所有触发HTTP上传任务的接口的参数列表里无法设置通知回调处理函数的通知都走这个通知，比如发送文件图片语音消息等）
  * @param[in] cb 下载的回调函数， nim_nos_upload_cb_func回调函数定义见nim_nos_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_nos_reg_upload_cb(nim_nos_upload_cb_func cb, const void *user_data);

/** @fn void nim_nos_download_media(const char *json_msg, nim_nos_download_cb_func res_cb, const void *res_user_data, nim_nos_download_prg_cb_func prg_cb, const void *prg_user_data)
  * 获取资源
  * @param[in] json_msg 消息体json string (Keys SEE MORE `nim_talk_def.h` 『消息结构 Json Keys』)
  * @param[in] res_cb 下载的回调函数， nim_nos_download_cb_func回调函数定义见nim_nos_def.h
  * @param[in] res_user_data APP的自定义用户数据，SDK只负责传回给回调函数res_cb，不做任何处理！
  * @param[in] prg_cb 下载进度的回调函数， nim_nos_download_prg_cb_func回调函数定义见nim_nos_def.h
  * @param[in] prg_user_data APP的自定义用户数据，SDK只负责传回给回调函数prg_cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				10206:下载暂停
  *				408:请求过程超时
  *				其他:参见HTTP协议或CURL错误码
  */
NIM_SDK_DLL_API void nim_nos_download_media(const char *json_msg, nim_nos_download_cb_func res_cb, const void *res_user_data, nim_nos_download_prg_cb_func prg_cb, const void *prg_user_data);

/** @fn void nim_nos_stop_download_media(const char *json_msg)
  * 停止获取资源（目前仅对文件消息类型有效）
  * @param[in] json_msg 消息体json string (Keys SEE MORE `nim_talk_def.h` 『消息结构 Json Keys』)
  * @return void 无返回值
  * @note 错误码	10206:成功
  */
NIM_SDK_DLL_API void nim_nos_stop_download_media(const char *json_msg);

/** @fn void nim_nos_upload(const char *local_file, nim_nos_upload_cb_func res_cb, const void *res_user_data, nim_nos_upload_prg_cb_func prg_cb, const void *prg_user_data)
  * 上传资源
  * @param[in] local_file 本地文件的完整路径，路径名必须是utf-8
  * @param[in] res_cb 上传的回调函数， nim_nos_upload_cb_func回调函数定义见nim_nos_def.h
  * @param[in] res_user_data APP的自定义用户数据，SDK只负责传回给回调函数res_cb，不做任何处理！
  * @param[in] prg_cb 上传进度的回调函数， nim_nos_upload_prg_cb_func回调函数定义见nim_nos_def.h
  * @param[in] prg_user_data APP的自定义用户数据，SDK只负责传回给回调函数prg_cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				408:请求过程超时
  *				其他:参见HTTP协议或CURL错误码
  */
NIM_SDK_DLL_API void nim_nos_upload(const char *local_file, nim_nos_upload_cb_func res_cb, const void *res_user_data, nim_nos_upload_prg_cb_func prg_cb, const void *prg_user_data);
/** @fn void nim_nos_upload2(const char *local_file,  const char *tag, nim_nos_upload_cb_func res_cb, const void *res_user_data, nim_nos_upload_prg_cb_func prg_cb, const void *prg_user_data)
* 上传资源
* @param[in] local_file 本地文件的完整路径，路径名必须是utf-8
* @param[in] tag 场景标签，主要用于确定文件的保存时间
* @param[in] res_cb 上传的回调函数， nim_nos_upload_cb_func回调函数定义见nim_nos_def.h
* @param[in] res_user_data APP的自定义用户数据，SDK只负责传回给回调函数res_cb，不做任何处理！
* @param[in] prg_cb 上传进度的回调函数， nim_nos_upload_prg_cb_func回调函数定义见nim_nos_def.h
* @param[in] prg_user_data APP的自定义用户数据，SDK只负责传回给回调函数prg_cb，不做任何处理！
* @return void 无返回值
* @note 错误码	200:成功
*				408:请求过程超时
*				其他:参见HTTP协议或CURL错误码
*/
NIM_SDK_DLL_API void nim_nos_upload2(const char *local_file, const char *tag, nim_nos_upload_cb_func res_cb, const void *res_user_data, nim_nos_upload_prg_cb_func prg_cb, const void *prg_user_data);
/** @fn void nim_nos_download(const char *nos_url, nim_nos_download_cb_func res_cb, const void *res_user_data, nim_nos_download_prg_cb_func prg_cb, const void *prg_user_data)
  * 下载资源
  * @param[in] nos_url 下载资源的URL
  * @param[in] res_cb 下载的回调函数， nim_nos_upload_cb_func回调函数定义见nim_nos_def.h
  * @param[in] res_user_data APP的自定义用户数据，SDK只负责传回给回调函数res_cb，不做任何处理！
  * @param[in] prg_cb 下载进度的回调函数， nim_nos_upload_prg_cb_func回调函数定义见nim_nos_def.h
  * @param[in] prg_user_data APP的自定义用户数据，SDK只负责传回给回调函数prg_cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				408:请求过程超时
  *				其他:参见HTTP协议或CURL错误码
  */
NIM_SDK_DLL_API void nim_nos_download(const char *nos_url, nim_nos_download_cb_func res_cb, const void *res_user_data, nim_nos_download_prg_cb_func prg_cb, const void *prg_user_data);

/** @fn void nim_nos_download_media_ex(const char *json_msg, const char *json_extension, nim_nos_download_cb_func res_cb, const void *res_user_data, nim_nos_download_prg_cb_func prg_cb, const void *prg_user_data, nim_nos_download_speed_cb_func speed_cb, const void *speed_user_data, nim_nos_download_info_cb_func info_cb, const void *info_user_data)
* 获取资源(扩展)
* @param[in] json_msg 消息体json string (Keys SEE MORE `nim_talk_def.h` 『消息结构 Json Keys』)
* @param[in] json_extension json扩展参数
* @param[in] res_cb 下载的回调函数， nim_nos_download_cb_func回调函数定义见nim_nos_def.h
* @param[in] res_user_data APP的自定义用户数据，SDK只负责传回给回调函数res_cb，不做任何处理！
* @param[in] prg_cb 下载进度的回调函数， nim_nos_download_prg_cb_func回调函数定义见nim_nos_def.h
* @param[in] prg_user_data APP的自定义用户数据，SDK只负责传回给回调函数prg_cb，不做任何处理！
* @param[in] speed_cb 下载速度的回调函数， nim_nos_download_speed_cb_func回调函数定义见nim_nos_def.h
* @param[in] speed_user_data APP的自定义用户数据，SDK只负责传回给回调函数speed_cb，不做任何处理！
* @param[in] info_cb 返回最终下载信息的回调函数， nim_nos_download_info_cb_func回调函数定义见nim_nos_def.h
* @param[in] info_user_data APP的自定义用户数据，SDK只负责传回给回调函数info_cb，不做任何处理！
* @return void 无返回值
* @note 错误码	200:成功
*				10206:下载暂停
*				408:请求过程超时
*				其他:参见HTTP协议或CURL错误码
*/
NIM_SDK_DLL_API void nim_nos_download_media_ex(const char *json_msg, const char *json_extension, nim_nos_download_cb_func res_cb, const void *res_user_data, nim_nos_download_prg_cb_func prg_cb, const void *prg_user_data, nim_nos_download_speed_cb_func speed_cb, const void *speed_user_data, nim_nos_download_info_cb_func info_cb, const void *info_user_data);

/** @fn void nim_nos_download_ex(const char *nos_url, const char *json_extension, nim_nos_download_cb_func res_cb, const void *res_user_data, nim_nos_download_prg_cb_func prg_cb, const void *prg_user_data, nim_nos_download_speed_cb_func speed_cb, const void *speed_user_data, nim_nos_download_info_cb_func info_cb, const void *info_user_data)
  * 下载资源(扩展)
  * @param[in] nos_url 下载资源的URL
    * @param[in] json_extension json扩展参数，拼接字段见 nim_nos_def.h "NOS扩展上传\下载接口参数json_extension Json key for nim_nos_upload_ex && nim_nos_download_ex"
  * @param[in] res_cb 下载的回调函数， nim_nos_upload_cb_func回调函数定义见nim_nos_def.h
  * @param[in] res_user_data APP的自定义用户数据，SDK只负责传回给回调函数res_cb，不做任何处理！
  * @param[in] prg_cb 下载进度的回调函数， nim_nos_upload_prg_cb_func回调函数定义见nim_nos_def.h
  * @param[in] prg_user_data APP的自定义用户数据，SDK只负责传回给回调函数prg_cb，不做任何处理！
  * @param[in] speed_cb 下载速度的回调函数， nim_nos_download_speed_cb_func回调函数定义见nim_nos_def.h
  * @param[in] speed_user_data APP的自定义用户数据，SDK只负责传回给回调函数speed_cb，不做任何处理！
  * @param[in] info_cb 返回最终下载信息的回调函数， nim_nos_download_info_cb_func回调函数定义见nim_nos_def.h
  * @param[in] info_user_data APP的自定义用户数据，SDK只负责传回给回调函数info_cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				10206:下载暂停
  *				408:请求过程超时
  *				其他:参见HTTP协议或CURL错误码
  */
NIM_SDK_DLL_API void nim_nos_download_ex(const char *nos_url, const char *json_extension, nim_nos_download_cb_func res_cb, const void *res_user_data, nim_nos_download_prg_cb_func prg_cb, const void *prg_user_data, nim_nos_download_speed_cb_func speed_cb, const void *speed_user_data, nim_nos_download_info_cb_func info_cb, const void *info_user_data);

/** @fn void nim_nos_stop_download_ex(const char *task_id, const char *json_extension);
  * 停止下载资源(只能用于调用了nim_nos_download_ex接口的下载任务)
  * @param[in] task_id 停止下载任务的ID
  * @param[in] json_extension json扩展参数
  * @return void 无返回值
  * @note 错误码	10206:成功
  *				其他:参见HTTP协议或CURL错误码
  */
NIM_SDK_DLL_API void nim_nos_stop_download_ex(const char *task_id, const char *json_extension);

/** @fn void nim_nos_upload_ex(const char *local_file, const char *json_extension, nim_nos_upload_cb_func res_cb, const void *res_user_data, nim_nos_upload_prg_cb_func prg_cb, const void *prg_user_data, nim_nos_upload_speed_cb_func speed_cb, const void *speed_user_data, nim_nos_upload_info_cb_func info_cb, const void *info_user_data)
* 上传资源(扩展)
* @param[in] local_file 本地文件的完整路径，路径名必须是utf-8
* @param[in] json_extension json扩展参数，拼接字段见 nim_nos_def.h "NOS扩展上传\下载接口参数json_extension Json key for nim_nos_upload_ex && nim_nos_download_ex"
* @param[in] res_cb 上传的回调函数， nim_nos_upload_cb_func回调函数定义见nim_nos_def.h
* @param[in] res_user_data APP的自定义用户数据，SDK只负责传回给回调函数res_cb，不做任何处理！
* @param[in] prg_cb 上传进度的回调函数， nim_nos_upload_prg_cb_func回调函数定义见nim_nos_def.h
* @param[in] prg_user_data APP的自定义用户数据，SDK只负责传回给回调函数prg_cb，不做任何处理！
* @param[in] speed_cb 上传速度的回调函数， nim_nos_upload_speed_cb_func回调函数定义见nim_nos_def.h
* @param[in] speed_user_data APP的自定义用户数据，SDK只负责传回给回调函数speed_cb，不做任何处理！
* @param[in] info_cb 返回最终上传信息的回调函数， nim_nos_upload_info_cb_func回调函数定义见nim_nos_def.h
* @param[in] info_user_data APP的自定义用户数据，SDK只负责传回给回调函数info_cb，不做任何处理！
* @return void 无返回值
* @note 错误码	200:成功
*				10200:上传暂停
*				408:请求过程超时
*				其他:参见HTTP协议或CURL错误码
*/
NIM_SDK_DLL_API void nim_nos_upload_ex(const char *local_file, const char *json_extension, nim_nos_upload_cb_func res_cb, const void *res_user_data, nim_nos_upload_prg_cb_func prg_cb, const void *prg_user_data, nim_nos_upload_speed_cb_func speed_cb, const void *speed_user_data, nim_nos_upload_info_cb_func info_cb, const void *info_user_data);

/** @fn void nim_nos_upload_ex2(const char *local_file,  const char *tag, const char *json_extension, nim_nos_upload_cb_func res_cb, const void *res_user_data, nim_nos_upload_prg_cb_func prg_cb, const void *prg_user_data, nim_nos_upload_speed_cb_func speed_cb, const void *speed_user_data, nim_nos_upload_info_cb_func info_cb, const void *info_user_data)
* 上传资源(扩展)
* @param[in] local_file 本地文件的完整路径，路径名必须是utf-8
* @param[in] tag 场景标签，主要用于确定文件的保存时间
* @param[in] json_extension json扩展参数，拼接字段见 nim_nos_def.h "NOS扩展上传\下载接口参数json_extension Json key for nim_nos_upload_ex && nim_nos_download_ex"
* @param[in] res_cb 上传的回调函数， nim_nos_upload_cb_func回调函数定义见nim_nos_def.h
* @param[in] res_user_data APP的自定义用户数据，SDK只负责传回给回调函数res_cb，不做任何处理！
* @param[in] prg_cb 上传进度的回调函数， nim_nos_upload_prg_cb_func回调函数定义见nim_nos_def.h
* @param[in] prg_user_data APP的自定义用户数据，SDK只负责传回给回调函数prg_cb，不做任何处理！
* @param[in] speed_cb 上传速度的回调函数， nim_nos_upload_speed_cb_func回调函数定义见nim_nos_def.h
* @param[in] speed_user_data APP的自定义用户数据，SDK只负责传回给回调函数speed_cb，不做任何处理！
* @param[in] info_cb 返回最终上传信息的回调函数， nim_nos_upload_info_cb_func回调函数定义见nim_nos_def.h
* @param[in] info_user_data APP的自定义用户数据，SDK只负责传回给回调函数info_cb，不做任何处理！
* @return void 无返回值
* @note 错误码	200:成功
*				10200:上传暂停
*				408:请求过程超时
*				其他:参见HTTP协议或CURL错误码
*/
NIM_SDK_DLL_API void nim_nos_upload_ex2(const char *local_file, const char *tag, const char *json_extension, nim_nos_upload_cb_func res_cb, const void *res_user_data, nim_nos_upload_prg_cb_func prg_cb, const void *prg_user_data, nim_nos_upload_speed_cb_func speed_cb, const void *speed_user_data, nim_nos_upload_info_cb_func info_cb, const void *info_user_data);

/** @fn void nim_nos_stop_upload_ex(const char *task_id, const char *json_extension);
* 停止上传资源(只能用于调用了nim_nos_upload_ex接口的上传任务)
* @param[in] task_id 停止上传任务的ID
* @param[in] json_extension json扩展参数
* @return void 无返回值
* @note 错误码	10200:成功
*				其他:参见HTTP协议或CURL错误码
*/
NIM_SDK_DLL_API void nim_nos_stop_upload_ex(const char *task_id, const char *json_extension);

/** @fn void nim_nos_set_quick_trans(int quick_trans);
* 设置是否支持快速上传
* @param[in] quick_trans 0：不支持，1：支持
* @return void 无返回值
* @note 默认支持快速上传
*/
NIM_SDK_DLL_API void nim_nos_set_quick_trans(int quick_trans);

/** @fn void nim_nos_safeurl_to_originurl(const char *safe_url, const char *json_extension, nim_nos_safeurl_to_originurl_cb_func callback_result, const void *user_data);
* 安全链接(短链)换源链接
* @param[in] safe_url 安全链接(短链)
* @param[in] json_extension 扩展字段
* @param[in] callback_result 查询 结果 回调
* @param[in] user_data 自定义数据，SDK只负责传回给回调函数callback_result，不做任何处理
* @return void 无返回值
* @note callback_result 200成功,404不存在的短链或不是有效的短链
*/
NIM_SDK_DLL_API void nim_nos_safeurl_to_originurl(const char *safe_url, const char *json_extension, nim_nos_safeurl_to_originurl_cb_func callback_result, const void *user_data);

#ifdef __cplusplus
};
#endif //__cplusplus
#endif //NIM_SDK_DLL_API_NIM_NOS_H_