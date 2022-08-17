/***********************************************
 *  液晶表示器ライブラリ originalをsakuが編集
 *  I2Cインターフェース　デジタル演習ボード用
 *    lcd_init()    ----- 初期化
 *    lcd_cmd(cmd)  ----- コマンド出力
 *    lcd_data(data) ----- １文字表示出力
 *    lcd_str(ptr)  ----- 文字列表示出力
 *    lcd_clear()   ----- 全消去
 **********************************************/
#include "lcd_lib.h"
#include "mcc_generated_files/i2c2_master.h"
#include "mcc_generated_files/mcc.h"

#define LCDADDR 0x3E        //LCD I2Cアドレス
/*********************************
 * 液晶へ1文字表示データ出力
 *********************************/
void lcd_data(char data)
{
    char tbuf[2]; // バッファ構成
    tbuf[0] = 0x40; // データ指定
    tbuf[1] = data; // 文字データ

    while (!I2C2_Open(LCDADDR)); //バス取得待ち　LCDADDR：LCDスレーブアドレス
    I2C2_SetBuffer(tbuf, 2); //2バイトバッファ指定
    I2C2_MasterWrite(); //送信実行

    while (I2C2_BUSY == I2C2_Close()); //送信終了待ち
    __delay_us(30); // 処置待ち遅延
}

/*******************************
 * 液晶へ１コマンド出力
 *******************************/
void lcd_cmd(char cmd)
{
    char tbuf[2]; // バッファ構成
    tbuf[0] = 0x00; // コマンド指定
    tbuf[1] = cmd; // コマンドデータ

    while (!I2C2_Open(LCDADDR)); //バス取得待ち　LCDADDR：LCDスレーブアドレス
    I2C2_SetBuffer(tbuf, 2); //2バイトバッファ指定
    I2C2_MasterWrite(); //送信実行

    while (I2C2_BUSY == I2C2_Close()); //送信終了待ち

    /* ClearかHomeか */
    if ((cmd == 0x01) || (cmd == 0x02))
        __delay_ms(2); // 2msec待ち
    else
        __delay_us(30); // 30μsec待ち
}

/*******************************
 *  初期化関数
 *******************************/
void lcd_init(void)
{
    __delay_ms(150); // 初期化待ち
    lcd_cmd(0x38); // 8bit 2line Normal mode
    lcd_cmd(0x39); // 8bit 2line Extend mode
    lcd_cmd(0x14); // OSC 183Hz BIAS 1/5
    /* コントラスト設定 */
    lcd_cmd(0x70 + (CONTRAST & 0x0F));
    lcd_cmd(0x5C + (CONTRAST >> 4));
    //    lcd_cmd(0x6B);            // Follower for 5.0V
    lcd_cmd(0x6B); // Follwer for 3.3V
    __delay_ms(300);
    lcd_cmd(0x38); // Set Normal mode
    lcd_cmd(0x0C); // Display On
    lcd_cmd(0x01); // Clear Display
}

/******************************
 * 全消去関数
 ******************************/
void lcd_clear(void)
{
    lcd_cmd(0x01); //初期化コマンド出力
}

/*****************************
 * 文字列表示関数
 *****************************/
void lcd_str(const char* ptr)
{
    while (*ptr != 0) //文字取り出し
        lcd_data(*ptr++); //文字表示
}

/*****************************
 *  アイコン表示制御関数
 *****************************/
void lcd_icon(unsigned int num, char onoff)
{
    lcd_cmd(0x39); // Extend mode
    lcd_cmd(0x40 + ICON[num][0]); // アイコンアドレス指定
    if (onoff)
        lcd_data(ICON[num][1]); // アイコンオンデータ
    else
        lcd_data(0x00); // アイコンオフデータ
    lcd_cmd(0x38); // Normal Mode
}
