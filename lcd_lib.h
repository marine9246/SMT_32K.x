/********************************
 *  液晶表示器用ヘッダファイル
 *  デジタル演習ボード用
 *    lcd_init()    ----- 初期化
 *    lcd_cmd(cmd)  ----- コマンド出力
 *    lcd_data(data) ----- １文字表示出力
 *    lcd_str(ptr)  ----- 文字列表示出力
 *    lcd_clear()   ----- 全消去
 ********************************/
#include <xc.h>
/********************************
*  調整用定数
*********************************/
//#define CONTRAST  0x18        // for 5.0V
#define CONTRAST  0x30      // for 3.3V
/*********************************
*　アイコンの定義
*********************************/
const unsigned int ICON[14][2]={
    {0x00, 0x10},       // アンテナ
    {0x02, 0x10},       // 電話
    {0x04, 0x10},       // 無線
    {0x06, 0x10},       // ジャック
    {0x07, 0x10},       // △
    {0x07, 0x08},       // ▽
    {0x07, 0x18},       // △▽
    {0x09, 0x10},       // 鍵
    {0x0B, 0x10},       // ピン
    {0x0D, 0x02},       // 電池無し
    {0x0D, 0x12},       // 容量少
    {0x0D, 0x1A},       // 容量中
    {0x0D, 0x1E},       // 容量多
    {0x0F, 0x10}        // 丸
};

void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_init(void);
void lcd_str(const unsigned char* ptr);
void lcd_clear(void);
void lcd_icon(unsigned int num, unsigned char onoff);
