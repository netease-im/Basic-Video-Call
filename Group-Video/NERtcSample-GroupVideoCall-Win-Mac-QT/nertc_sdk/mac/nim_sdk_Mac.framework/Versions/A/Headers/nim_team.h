/** @file nim_team.h
  * @brief 群组 接口头文件
  * @copyright (c) 2015-2017, NetEase Inc. All rights reserved
  * @author Harrison
  * @date 2015/2/1
  */
#ifndef NIM_SDK_DLL_API_NIM_TEAM_H_
#define NIM_SDK_DLL_API_NIM_TEAM_H_

#include "public_define/defines/nim_sdk_dll.h"
#include "public_define/defines/nim_define/nim_team_def.h"

#ifdef __cplusplus
extern"C"
{
#endif
/** @fn void nim_team_reg_team_event_cb(const char *json_extension, nim_team_event_cb_func cb, const void *user_data)
  * (全局回调)统一注册接收群通知回调函数（收到的群通知通过此接口广播）
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		群通知的回调函数, nim_team_event_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_team_reg_team_event_cb(const char *json_extension, nim_team_event_cb_func cb, const void *user_data);

/** @fn void nim_team_create_team_async(const char *team_info, const char *jsonlist_uids, const char *invitation_postscript, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 创建群组
  * @param[in] team_info team信息的json string (Keys SEE MORE nim_team_def.h『群组信息 Json Keys』 as follows)
  * @param[in] jsonlist_uids		uids string array 不包括自己
  * @param[in] invitation_postscript 邀请附言
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		群通知的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				810:如果创建的是高级群，返回810表示邀请成功并带上tinfo
  *				414:成员不足
  *				801:成员数超限制
  *				404:成员中有非法用户
  */
NIM_SDK_DLL_API void nim_team_create_team_async(const char *team_info, 
	const char *jsonlist_uids, 
	const char *invitation_postscript,
	const char *json_extension, 
	nim_team_opt_cb_func cb,
	const void *user_data);

/** @fn void nim_team_invite_async(const char *tid, const char *jsonlist_uids, const char *invitation_postscript, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 邀请
  * @param[in] tid		群组id
  * @param[in] jsonlist_uids		uids string array
  * @param[in] invitation_postscript 邀请附言
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		邀请的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				810:如果是高级群，返回810表示邀请成功并带上timetag
  *				404:非法用户
  *				801:群人数超限
  *				802:没有权限
  *				803:群不存在
  */
NIM_SDK_DLL_API void nim_team_invite_async(const char *tid, 
	const char *jsonlist_uids, 
	const char *invitation_postscript, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_invite_async2(const char *tid, const char *jsonlist_uids, const char *invitation_postscript, const char *invitation_attachment,const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 邀请
  * @param[in] tid		群组id
  * @param[in] jsonlist_uids		uids string array
  * @param[in] invitation_postscript 邀请附言
  * @param[in] invitation_attachment 用户可自定义的补充邀请信息
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		邀请的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				810:如果是高级群，返回810表示邀请成功并带上timetag
  *				404:非法用户
  *				801:群人数超限
  *				802:没有权限
  *				803:群不存在
  */
NIM_SDK_DLL_API void nim_team_invite_async2(const char *tid,
	const char *jsonlist_uids,
	const char *invitation_postscript,
	const char *invitation_attachment,
	const char *json_extension,
	nim_team_opt_cb_func cb,
	const void *user_data);
/** @fn void nim_team_kick_async(const char *tid, const char *jsonlist_uids, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 踢人
  * @param[in] tid		群组id
  * @param[in] jsonlist_uids		uids string array
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		踢人的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				403:被踢的是管理员或群主
  *				404:非法用户
  *				801:群人数超限
  *				802:没有权限
  *				803:群不存在
  */
NIM_SDK_DLL_API void nim_team_kick_async(const char *tid, 
	const char *jsonlist_uids, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_leave_async(const char *tid, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 离开群
  * @param[in] tid		群组id
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		离开群的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				803:群不存在
  *				804:用户不在群里
  */
NIM_SDK_DLL_API void nim_team_leave_async(const char *tid, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_dismiss_async(const char *tid, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 解散群
  * @param[in] tid		群组id
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		解散群的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				802:没有权限
  *				803:群不存在
  */
NIM_SDK_DLL_API void nim_team_dismiss_async(const char *tid, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_update_team_info_async(const char *tid, const char *json_info, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 更新群信息
  * @param[in] tid		群组id
  * @param[in] json_info Json string array (Keys SEE MORE `nim_team_def.h` 『群组信息 Json Keys』， 目前只支持更新群名称，群id必需填)
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		更新群信息的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				802:没有权限
  *				803:群不存在
  */
NIM_SDK_DLL_API void nim_team_update_team_info_async(const char *tid, 
	const char *json_info, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_apply_join_async(const char *tid, const char *reason, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 申请入群
  * @param[in] tid		群组id
  * @param[in] reason	附言
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		申请入群的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				802:群验证方式为拒绝所有人申请
  *				808:申请成功，等待验证
  *				809:已经在群里
  *				801:人数限制
  *				803:群不存在
  *				805:群类型不对
  */
NIM_SDK_DLL_API void nim_team_apply_join_async(const char *tid, 
	const char *reason, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_pass_join_apply_async(const char *tid, const char *applicant_id, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 同意入群申请
  * @param[in] tid		群组id
  * @param[in] applicant_id	申请者id
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		同意入群申请的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				509:操作已失效
  *				809:已经在群里
  *				801:人数限制
  *				802:没有权限
  *				803:群不存在
  *				805:群类型不对
  */
NIM_SDK_DLL_API void nim_team_pass_join_apply_async(const char *tid, 
	const char *applicant_id, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_reject_join_apply_async(const char *tid, const char *applicant_id, const char *reason, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 拒绝入群申请
  * @param[in] tid		群组id
  * @param[in] applicant_id	申请者id
  * @param[in] reason		附言
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		拒绝入群申请的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功，如果用户处于申请状态则会通知申请用户被拒绝
  *				509:操作已失效
  *				802:没有权限
  *				803:群不存在
  *				805:群类型不对
  */
NIM_SDK_DLL_API void nim_team_reject_join_apply_async(const char *tid, 
	const char *applicant_id, 
	const char *reason, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_add_managers_async(const char *tid, const char *jsonlist_admin_ids, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 添加管理员
  * @param[in] tid		群组id
  * @param[in] jsonlist_admin_ids	uids string array
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		添加管理员的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				802:没有权限
  *				803:群不存在
  *				805:群类型不对
  */
NIM_SDK_DLL_API void nim_team_add_managers_async(const char *tid, 
	const char *jsonlist_admin_ids, 
	const char *json_extension,
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_remove_managers_async(const char *tid, const char *jsonlist_admin_ids, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 删除管理员
  * @param[in] tid		群组id
  * @param[in] jsonlist_admin_ids	uids string array
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		删除管理员的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				802:没有权限
  *				803:群不存在
  *				805:群类型不对
  */
NIM_SDK_DLL_API void nim_team_remove_managers_async(const char *tid, 
	const char *jsonlist_admin_ids, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_transfer_team_async(const char *tid, const char *new_owner, bool is_leave, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 移交群主
  * @param[in] tid		群组id
  * @param[in] new_owner	移交对象uid
  * @param[in] is_leave		是否同时退出群
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		移交群主的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				802:没有权限
  *				803:群不存在
  *				805:群类型不对
  *				806:群数量上限
  */
NIM_SDK_DLL_API void nim_team_transfer_team_async(const char *tid, 
	const char *new_owner, 
	bool is_leave, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_update_my_property_async(const char *info, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 更新自己的群属性
  * @param[in] info		json string 群组成员信息,包含tid和需要修改的字段（目前支持修改kNIMTeamUserKeyNick、kNIMTeamUserKeyBits、kNIMTeamUserKeyCustom三个字段） (Keys SEE MORE `nim_team_def.h` 『群组属性 Json Keys』
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		更新自己的群属性的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				803:群不存在
  *				804:不在群里
  *				805:群类型不对
  */
NIM_SDK_DLL_API void nim_team_update_my_property_async(const char *info, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_update_other_nick_async(const char *info, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 修改别人的群昵称
  * @param[in] info		json string tlist 包含tid,accid,nick字段 (Keys SEE MORE `nim_team_def.h` 『群组属性 Json Keys』
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		修改别人的群昵称的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				802:没有权限
  *				803:群不存在
  *				804:不在群里
  *				805:群类型不对
  */
NIM_SDK_DLL_API void nim_team_update_other_nick_async(const char *info, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_accept_invitation_async(const char *tid, const char *invitor, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 接受邀请
  * @param[in] tid		群组id
  * @param[in] invitor	邀请者id
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		接受邀请的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				802:没有权限
  *				803:群不存在
  *				805:群类型不对
  */
NIM_SDK_DLL_API void nim_team_accept_invitation_async(const char *tid, 
	const char *invitor, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_reject_invitation_async(const char *tid, const char *invitor, const char *reason, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 拒绝邀请
  * @param[in] tid		群组id
  * @param[in] invitor	邀请者id
  * @param[in] reason	附言
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		拒绝邀请的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				802:没有权限
  *				803:群不存在
  *				805:群类型不对
  */
NIM_SDK_DLL_API void nim_team_reject_invitation_async(const char *tid, 
	const char *invitor, 
	const char *reason, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_query_all_my_teams_async(const char *json_extension, nim_team_query_all_my_teams_cb_func cb, const void *user_data)
  * 查询本地所有群（有效群-群有效AND我在群里-）
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		查询所有群的回调函数, nim_team_query_all_my_teams_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_team_query_all_my_teams_async(const char *json_extension, 
	nim_team_query_all_my_teams_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_query_all_my_teams_info_async(const char *json_extension, nim_team_query_all_my_teams_info_cb_func cb, const void *user_data)
  * 查询本地所有群信息（默认查询有效群-群有效AND我在群里-）
  * @param[in] json_extension 扩展参数，可以条件获取缓存中有的无效群(我已经不在里面的群OR解散的群)，SDK2.7.0以上支持，例如 "{"include_invalid" : true}"，参数可查询nim_team_def.h 搜索本地群组相关信息扩展参数
  * @param[in] cb		查询所有群信息的回调函数, nim_team_query_all_my_teams_info_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_team_query_all_my_teams_info_async(const char *json_extension, 
	nim_team_query_all_my_teams_info_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_query_my_all_member_infos_async(const char *json_extension, nim_team_query_my_all_member_infos_cb_func cb, const void *user_data)
  * 查询本地所有群里我的成员信息（使用场景：获取了所有群列表后，需要查询自己在每个群里自己的成员信息，使用成员信息里的bits字段，可以判断当某个群发来消息后，是否做消息通知）
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		 查询我的所有群里我的成员信息的回调函数, nim_team_query_my_all_member_infos_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_team_query_my_all_member_infos_async(const char *json_extension,
	nim_team_query_my_all_member_infos_cb_func cb,
	const void *user_data);

/** @fn void nim_team_query_team_members_async(const char *tid, bool include_user_info, const char *json_extension, nim_team_query_team_members_cb_func cb, const void *user_data)
  * 查询群成员（默认查询有效群成员-在群里-）
  * @param[in] tid		群组id
  * @param[in] include_user_info 返回结果中是否包含成员信息(关系到如何解析返回的json)
  * @param[in] json_extension 扩展参数，如果include_user_info为true，可以条件获取缓存中有的无效群成员（不在群里了），SDK2.8.0以上支持，例如 "{"include_invalid" : true}"，参数可查询nim_team_def.h 搜索本地群组相关信息扩展参数
  * @param[in] cb		查询群成员的回调函数, nim_team_query_team_members_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码 200:成功
  *				406:没有变化
  *				802:没有权限
  */
NIM_SDK_DLL_API void nim_team_query_team_members_async(const char *tid, 
	bool include_user_info, 
	const char *json_extension, 
	nim_team_query_team_members_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_query_team_member_async(const char *tid, const char *user_id, const char *json_extension, nim_team_query_team_member_cb_func cb, const void *user_data)
  * 查询(单个)群成员信息(如果缓存中有数据，支持有效或无效成员)
  * @param[in] tid		群组id
  * @param[in] user_id  群成员id
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		查询群成员的回调函数, nim_team_query_team_member_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_team_query_team_member_async(const char *tid, 
	const char *user_id, 
	const char *json_extension, 
	nim_team_query_team_member_cb_func cb, 
	const void *user_data);

/** @fn char *nim_team_query_team_member_block(const char *tid, const char *user_id)
  * 查询(单个)群成员信息(如果缓存中有数据，支持有效或无效成员)(同步接口，堵塞NIM内部线程，谨慎使用)
  * @param[in] tid		群组id
  * @param[in] user_id  群成员id
  * @return char * 返回群成员信息Json char,需要上层调用nim_global.h提供的内存释放接口释放。
  */
NIM_SDK_DLL_API char *nim_team_query_team_member_block(const char *tid, const char *user_id);

/** @fn void nim_team_query_team_info_async(const char *tid, const char *json_extension, nim_team_query_team_info_cb_func cb, const void *user_data)
  * 本地查询群信息(如果缓存中有数据，支持有效或无效群)
  * @param[in] tid		群组id
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		查询群信息的回调函数, nim_team_query_team_info_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_team_query_team_info_async(const char *tid, 
	const char *json_extension, 
	nim_team_query_team_info_cb_func cb, 
	const void *user_data);

/** @fn char *nim_team_query_team_info_block(const char *tid)
  * 本地查询群信息(如果缓存中有数据，支持有效或无效群)(同步接口，堵塞NIM内部线程，谨慎使用)
  * @param[in] tid		群组id
  * @return char * 返回群信息Json char, 需要上层调用nim_global.h提供的内存释放接口释放。
  */
NIM_SDK_DLL_API char *nim_team_query_team_info_block(const char *tid);

/** @fn void nim_team_query_team_info_online_async(const char *tid, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 在线查询群信息（从服务器获取）
  * @param[in] tid		群组id
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		获取群信息的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				803:群不存在
  */

NIM_SDK_DLL_API void nim_team_query_team_info_online_async(const char *tid, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_mute_member_async(const char *tid, const char *member_id, bool set_mute, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
  * 对群成员禁言/解除禁言
  * @param[in] tid		群组id
  * @param[in] member_id 群成员id
  * @param[in] set_mute	禁言(true)、解除禁言(false)
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		拒绝邀请的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				404:禁言对象不存在 
  *				414:参数错误
  *				803:群不存在
  *				802:没有权限	
  */
NIM_SDK_DLL_API void nim_team_mute_member_async(const char *tid, 
	const char *member_id, 
	bool set_mute, 
	const char *json_extension, 
	nim_team_opt_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_query_mute_list_online_async(const char *tid, const char *json_extension, nim_team_query_mute_list_cb_func cb, const void *user_data)
  * 获取群禁言成员列表
  * @param[in] tid		群组id
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @param[in] cb		拒绝邀请的回调函数
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  * @note 错误码	200:成功
  *				803:群不存在
  *				802:没有权限
  */
NIM_SDK_DLL_API void nim_team_query_mute_list_online_async(const char *tid, 
	const char *json_extension, 
	nim_team_query_mute_list_cb_func cb, 
	const void *user_data);

/** @fn void nim_team_mute_async(const char *tid, bool set_mute, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data)
* 对群禁言/解除禁言
* @param[in] tid		群组id
* @param[in] set_mute	禁言(true)、解除禁言(false)
* @param[in] json_extension json扩展参数（备用，目前不需要）
* @param[in] cb		拒绝邀请的回调函数, nim_team_opt_cb_func回调函数定义见nim_team_def.h
* @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
* @return void 无返回值
* @note 错误码	200:成功
*				414:参数错误
*/
NIM_SDK_DLL_API void nim_team_mute_async(const char *tid,
	bool set_mute,
	const char *json_extension,
	nim_team_opt_cb_func cb,
	const void *user_data);

/** @fn void nim_team_msg_ack_read(const char *tid, const char *json_msgs, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data);
* 群消息回执
* @param[in] tid		群组id
* @param[in] json_msgs	需要发送消息回执的群消息json array
* @param[in] json_extension json扩展参数（备用，目前不需要）
* @param[in] cb		回调函数, 定义见nim_team_def.h
* @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
* @return void 无返回值
* @note 错误码	200:成功
*				414:参数错误
*/
NIM_SDK_DLL_API void nim_team_msg_ack_read(const char *tid, const char *json_msgs, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data);

/** @fn void nim_team_msg_query_unread_list(const char *tid, const char *json_msg, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data);
* 获取群消息未读成员列表
* @param[in] tid		群组id
* @param[in] json_msg	群消息json
* @param[in] json_extension json扩展参数（备用，目前不需要）
* @param[in] cb		回调函数, 定义见nim_team_def.h
* @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
* @return void 无返回值
* @note 错误码	200:成功
*				414:参数错误
*/
NIM_SDK_DLL_API void nim_team_msg_query_unread_list(const char *tid, const char *json_msg, const char *json_extension, nim_team_opt_cb_func cb, const void *user_data);

/** @fn void nim_team_query_members_invitor(const char *tid, const char *members,  nim_team_query_members_invitor_cb_func cb,const void *user_data);
* 查询群成员的邀请人 accid
* @param[in] tid		群组id
* @param[in] members	群成员accid列表 json array
* @param[in] cb		回调函数, 定义见nim_team_def.h
* @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
* @return void 无返回值
* @note 错误码	200:成功
*/
NIM_SDK_DLL_API void nim_team_query_members_invitor(const char *tid, const char *members,  nim_team_query_members_invitor_cb_func cb,const void *user_data);

/** @fn void nim_team_query_teams_info_by_keyword(const char *keyword, nim_team_query_all_my_teams_cb_func cb, const char *json_extension, const void *user_data);
* 查询群成员的邀请人 accid
* @param[in] keyword		要查询的关键字
* @param[in] query_type		查询条件，见：NIMTeamQueryType
* @param[in] cb				查询群信息的回调函数
* @param[in] json_extension json扩展参数（备用，目前不需要）
* @param[in] user_data		APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
* @return void 无返回值
* @note 错误码	200:成功
*/
NIM_SDK_DLL_API void nim_team_query_teams_info_by_keyword(const char *keyword, 
	nim_team_query_all_my_teams_cb_func cb, 
	const char *json_extension, 
	const void *user_data);

/** @fn void nim_team_get_team_info_batch_sftrans(const char *json_extension, nim_team_query_all_my_teams_info_cb_func cb, const void *user_data)
  * 查询所有群信息（顺丰专用）
  * @param[in] json_extension 扩展参数，可以条件获取缓存中有的无效群(我已经不在里面的群OR解散的群)，SDK2.7.0以上支持，例如 "{"include_invalid" : true}"，参数可查询nim_team_def.h 搜索本地群组相关信息扩展参数
  * @param[in] cb		查询所有群信息的回调函数, nim_team_query_all_my_teams_info_cb_func回调函数定义见nim_team_def.h
  * @param[in] time_tag 时间戳，没有特殊需求此参数赋0
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_team_get_team_info_batch_sftrans(const char *json_extension, nim_team_query_all_my_teams_info_cb_func cb,
   uint64_t time_tag, const void* user_data);

/** @fn void nim_team_update_tinfo_local(const char *json_info_list,	nim_team_update_tinfo_local_cb_func cb_func, const bool notify_event, const void* user_data);
  * 更新本地缓存的群信息（顺丰专用）
  * @param[in] json_info_list 要更新的群信息
  * @param[in] cb_func	 结果回调
  * @param[in] notify_event	 就否触发群信息更新事件
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_team_update_tinfo_local(const char *json_info_list,
	nim_team_update_tinfo_local_cb_func cb_func, const void* user_data);

#ifdef __cplusplus
};
#endif //__cplusplus
#endif //NIM_SDK_DLL_API_NIM_TEAM_H_
