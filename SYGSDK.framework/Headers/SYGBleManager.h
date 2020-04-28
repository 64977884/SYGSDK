//
//  SYGBleManager.h
//  SYGPen
//
//  Created by Bruce on 2018/12/20.
//  Copyright © 2018 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "SYGOfflineStatusManager.h"
#import "SYGBleStartData.h"
#import "SYGBleBatteryStatus.h"
#import "CBPeripheralRSSI.h"
#import "SYGPaperInfo.h"
#import "SYGPaperXYInfo.h"
#import "SYGBlePenInfo.h"
#import "SYGWriteCodeDecoder.h"
NS_ASSUME_NONNULL_BEGIN

extern NSString * const SYGBluetoothDisConnectNotification;
extern NSString * const SYGBluetoothBeginWriteNotification;

@protocol SYGBleManagerDelegate <NSObject>

@optional

/**
 蓝牙权限已打开
 */
- (void)bluetoothPrivacyDidOpen;

/**
 蓝牙权限已关闭
 */
- (void)bluetoothPrivacyDidClosed;

/**
 发现蓝牙笔

 @param peripherals 蓝牙笔数组
 */
- (void)didDiscoverPeripherals:(NSArray<CBPeripheralRSSI *> *)peripherals;

/**
 蓝牙笔连接成功
 */
- (void)didConnectPeripheral;

/**
 蓝牙笔连接失败

 @param error 失败原因x
 */
- (void)didFailToConnectPeripheral:(NSError *)error;

/**
 蓝牙笔断开连接
 */
- (void)didDisconnectPeripheral;

/**
 扫描蓝牙设备超时
 */
- (void)scanPeripheralsTimeOut;

/**
 蓝牙笔落笔

 @param startData 蓝牙笔开始书写信息
 */
- (void)writeDownStartData:(SYGBleStartData *)startData;

/**
 蓝牙笔移动
 
 @param paperXYInfo 码纸及坐标信息
 */
- (void)writeMovePaperXYInfo:(SYGPaperXYInfo *)paperXYInfo;

/**
 蓝牙笔抬笔

 @param strokeNum 笔画的发送序号
 @param pointNum 笔画坐标点个数
 @param endTime 笔画结束时间
 @param imgNum 解码缓存没有解码完成的图像帧数目
 @param failDotNum 解码失败的坐标个数
 */
- (void)writeUpStrokeNum:(long)strokeNum pointNum:(long)pointNum endTime:(long)endTime imgNum:(long)imgNum failDot:(long)failDotNum;

/**
 蓝牙笔不支持的物理页码

 @param errorMsg 异常信息
 */
- (void)unSupportPageError:(NSString *)errorMsg;

/**
网络码纸有效期失效，请重新获取网络码纸信息，并设置

@param errorMsg 异常信息
*/
- (void)paperExpiredError:(NSString *)errorMsg;

/**
未设置网络码纸资源

@param errorMsg 异常信息
*/
- (void)unSetNetworkPaperResource:(NSString *)errorMsg;

/**
 离线状态

 @param status 离线状态枚举类型
 */
- (void)offlineWithStatus:(SYGOfflineStatus)status;

/**
 离线数据长度

 @param length 离线数据长度
 */
- (void)offlineDataLength:(NSInteger)length;

/**
 蓝牙笔电量状态

 @param batteryLevel 电量状态枚举类型
 */
- (void)batteryLevel:(SYGBleBatteryLevel)batteryLevel;

/**
 主动查询蓝牙笔电量状态

 @param batteryLevel 电量状态枚举类型
 */
- (void)initiativeBatteryLevel:(SYGBleBatteryLevel)batteryLevel;

/**
 蓝牙笔基本信息

  @param blePenInfo 基本信息对象
*/
- (void)blePenInfo:(SYGBlePenInfo *)blePenInfo;

/**
 写命令是否成功回调，调用以下方法，都会走该代理方法
 sendOfflineDataLengthCmd
 sendBlePenTimeCmd:
 sendTransferOfflineDataCmd:
 sendBatteryStatusCmd
 sendBatteryIntervalCmdWithSeconds:
 @param error error nil: 成功 非nil: 失败
 */
- (void)writeCmdError:(NSError *)error;

@end

@interface SYGBleManager : NSObject

@property (nonatomic, weak) id <SYGBleManagerDelegate> delegate;

/**
 是否打印调试日志
 Release模式关闭
 Debug模式 默认关闭 可设置YES为开启
*/
@property (nonatomic, assign) BOOL debugLogEnabled;

/**
 当前是否已连接蓝牙笔
 */
@property (nonatomic, assign) BOOL isConnect;

/**
 当前已连接蓝牙笔的peripheral
 */
@property (nonatomic, strong) CBPeripheral *peripheral;

/**
 当前已连接蓝牙笔的设备号标识符
 */
@property (nonatomic, copy) NSString *connectIdentifity;

/**
是否过滤笔画噪点（默认为YES）
*/
@property (nonatomic, assign) BOOL isFilterBleData;

/**
是否本地码纸解码（默认为NO）
*/
@property (nonatomic, assign) BOOL isLocalDecoder;

/**
 网络码纸资源是否有效（是否存在过期的）
 使用这个属性前，请先调用configNetworkPaperResource方法，以便设置网络码纸资源。
 如果不设置，则默认为NO
*/
@property (nonatomic, assign) BOOL isInvalidNetworkPaperResource;

/// 网络码纸数据
@property (nonatomic, strong) SYGWriteCodeDecoder *networkWriteCodeDecoder;
/**
 设置扫描附近蓝牙设备超时时间（单位为毫秒，默认为10秒）
  请在调用initCentralManager方法前，设置扫描超时时间
*/
@property (nonatomic, assign) NSInteger scanTimeOut;

/// 所有采集失败的点个数
@property(nonatomic)NSInteger failDots;

+ (instancetype)sharedManager;

/**
 初始化centralManager
 调用该方法后，就会自动去扫码蓝牙设备
 */
- (void)initCentralManager;

/**
 蓝牙笔连接成功后，停止扫描蓝牙设备
 默认在连接成功后，就会调用该方法。
 */
- (void)stopScan;

/**
 重新扫描，如果当前正在扫描，调用该方法，不会执行任何操作。
 */
- (void)retrieveScan;

/**
 重新连接蓝牙笔

 @param pRSSI CBPeripheralRSSI对象
 */
- (void)connectPeripheralWithCBPeripheralRSSI:(CBPeripheralRSSI *)pRSSI;

/**
 重新连接蓝牙笔

 @param peri CBPeripheral对象
 */
- (void)connectPeripheralWithCBPeripheral:(CBPeripheral *)peri;

/**
 重新连接蓝牙笔

 @param identifity 重连蓝牙笔的设备号 可通过connectIdentifity属性拿到
 */
- (void)retrieveConnectedPeripheralsWithIdentifity:(NSString *)identifity;

/**
 断开蓝牙笔连接
 */
- (void)cancelPeripheralConnection;

/**
 主动查询蓝牙笔离线数据长度
 在delegate方法offlineDataLength:可以获取到离线数据长度
 */
- (void)sendOfflineDataLengthCmd;

/**
 是否传输蓝牙笔离线数据

 @param transfer YES: 传输 NO:不传输
 */
- (void)sendTransferOfflineDataCmd:(BOOL)transfer;

/**
 主动查询蓝牙笔电量
 */
- (void)sendBatteryStatusCmd;

/**
 设置蓝牙笔电量通知间隔时间

 @param seconds 单位秒 (范围 5~256)
 */
- (void)sendBatteryIntervalCmdWithSeconds:(int)seconds;

/**
 重新设置蓝牙笔当前时间戳

 @param time  (毫秒时间戳)
*/
- (void)sendResetBlePenLocalTimeCmdWithTime:(long)time;

/**
  获取蓝牙笔基本信息，获得的信息在协议方法里面取得
    - (void)blePenInfo:(SYGBlePenInfo *)blePenInfo;
*/
- (void)sendBlePenInfoCmd;

/**
设置网络码纸资源

@param paperInfos  网络码纸资源
*/
- (void)configNetworkPaperResource:(NSArray<SYGPaperInfo *> *)paperInfos;

@end

NS_ASSUME_NONNULL_END
