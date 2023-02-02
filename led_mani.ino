#include "edp.c"

#define KEY "GAQoITsDTBl=DFEYkXhApwj4RdQ=" //APIkey [需要修改]!!! 
#define ID "758387593" //设备ID [需要修改]!!! 

//#define PUSH_ID "680788" 
#define PUSH_ID NULL 
String comdata = "";
// 定义串口初始化 
#define _baudrate 115200
#define WIFI_UART Serial 
int light = 0; 


//定义数码管端口
const int stbPin = 7; //the segment display module STB pin connected to digital pin 7 
const int clkPin = 9; //the segment display module CLK pin connected to digital pin 9 
const int dioPin = 8; //the segment display module DIO pin connected to digital pin 8 
int redpin=9;
int grepin=10;
int blupin=11;

//定义数组代表0-9显示 
uint8_t digits[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f };
edp_pkt *pkt;

/** doCmdOk 判断回复内容是否符合 * 发送命令至模块，从回复中获取期待的关键字 * keyword: 所期待的关键字 * 成功找到关键字返回true，否则返回false */

bool doCmdOk(String data, char *keyword)
{ 
  bool result = false;
  
  if (data != "") //对于tcp连接命令，直接等待第二次回复 
  {
    WIFI_UART.println(data); //发送AT指令 
    }
    if (data == "AT") //检查模块存在
    delay(2000);
    else
    while (!WIFI_UART.available());
    // 等待模块回复
    
    delay(200); 
    
    if (WIFI_UART.find(keyword)) 
    //返回值判断
    { 
      result = true;
      }
      else
      { 
        result = false;
      }
      while (WIFI_UART.available())
      WIFI_UART.read();
     //清空串口接收缓存 
     delay(500); 
     //指令时间间隔
      return result;
      }

//数码管初始化
void sendCommand(uint8_t value)

{ 
  digitalWrite(stbPin, LOW);

shiftOut(dioPin, clkPin, LSBFIRST, value);

digitalWrite(stbPin, HIGH); 
}

/*此部分为ESP8266连接WiFi */

void setup()
{ 
  char buf[100] = {0};
  int tmp;
  
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT); //用于连接EDP控制的发光二极管

  
  WIFI_UART.begin( _baudrate );
  pinMode(stbPin, OUTPUT); 
  pinMode(clkPin, OUTPUT); 
  pinMode(dioPin, OUTPUT); 
  sendCommand(0x8f); //activate 
  WIFI_UART.setTimeout(3000);  
  delay(3000);
  Serial.setTimeout(100);
  
  delay(2000); 
  while (!doCmdOk("AT", "OK"));
  digitalWrite(13, HIGH);
  while (!doCmdOk("AT+CWMODE=3", "OK"));
  
 
  while (!doCmdOk("AT+CWJAP=\"awwwwman\",\"20050512\"", "OK"));//WiFi账号与 WiFi密码 [需要修改]!!!
  while (!doCmdOk("AT+CIPSTART=\"TCP\",\"jjfaedp.hedevice.com\",876", "OK")); //连接onenet TPC接口 
  while (!doCmdOk("AT+CIPMODE=1", "OK")); //透传模式 
  while (!doCmdOk("AT+CIPSEND", ">")); //开始发送
  } 
  int light_flag = 1; 

            /** packetSend * 将待发数据发送至串口，并释放到动态分配的内存 */
void packetSend(edp_pkt* pkt) 
{ 
  if (pkt != NULL) 
  { 
    WIFI_UART.write(pkt->data, pkt->len);
    //串口发送 
    WIFI_UART.flush();
    free(pkt);
    //回收内存 
    } }

    bool readEdpPkt(edp_pkt *p) 
          { int tmp;
          if ((tmp = WIFI_UART.readBytes(p->data + p->len, sizeof(p->data))) > 0 ) 
          { rcvDebug(p->data + p->len, tmp);
          p->len += tmp;
          }
          return true;
          }

              void rcvDebug(unsigned char *rcv, int len)
              { int i; }
              
  void loop() 
  { 
    static int edp_connect = 0;
    bool trigger = false;
    edp_pkt rcv_pkt;
    unsigned char pkt_type;
    int i = 0, tmp;
    char num[10];
    int intensity;
    char intensity1[20];
    
    /* EDP 连接 */
    if (!edp_connect)
    { 
      while (WIFI_UART.available()) WIFI_UART.read();//清空串口接收缓存
      packetSend(packetConnect(ID, KEY)); //发送EPD连接包
      while (!WIFI_UART.available()); //等待EDP连接应答
      if ((tmp = WIFI_UART.readBytes(rcv_pkt.data, sizeof(rcv_pkt.data))) > 0 ) 
      { rcvDebug(rcv_pkt.data, tmp); 
      //平台连接成功会返回特殊数据，判断，否则清空
      if (rcv_pkt.data[0] == 0x20 && rcv_pkt.data[2] == 0x00 && rcv_pkt.data[3] == 0x00)
      { 
        edp_connect = 1;
        digitalWrite(13, LOW);
        // 使Led灭
        }
        else ; 
        }
        packetClear(&rcv_pkt);
        //该函数上传温湿度信息
        }

        
        if(light_flag == 1)
        { 
        light_flag = 0;
        
        intensity=analogRead(A1);
       
        sprintf(intensity1,"%d",intensity);
        //int型转换char型
        light = 0;
        delay(500);
        //char intensity2[]="fghjklwteeryryaeyra";
        packetSend(packetDataSaveTrans(NULL, "intensity", intensity1)); 
        //将新数据值上传至数据流 WD是 上传的地方 wd1是上传的数据
        delay(500); 
        } 
        
        light++; 
        
        if(light > 150&&edp_connect)
        { 
         intensity=analogRead(A1);
        
         sprintf(intensity1,"%d",intensity);
          light = 0; 
          delay(500);
           packetSend(packetDataSaveTrans(NULL, "intensity", intensity1)); 
        //将新数据值上传至数据流 WD是 上传的地方 wd1是上传的数据
        delay(500); 
        
      }
       
      while (WIFI_UART.available())
      { 
        readEdpPkt(&rcv_pkt);
      
      if (isEdpPkt(&rcv_pkt))
      { 
        pkt_type = rcv_pkt.data[0];
        
        switch (pkt_type)
        { 
          case CMDREQ: 
          char edp_command[50];
          char edp_cmd_id[40];
          long id_len, cmd_len, rm_len;
          char datastr[20];
          char val[10]; 
          memset(edp_command, 0, sizeof(edp_command));
          memset(edp_cmd_id, 0, sizeof(edp_cmd_id)); 
          edpCommandReqParse(&rcv_pkt, edp_cmd_id, edp_command, &rm_len, &id_len, &cmd_len); 
        
          //数据处理与应用中EDP命令内容对应 
          //本例中格式为 datastream:[1/0] 
          
          sscanf(edp_command, "%[^:]:%s", datastr, val); 
          Serial.println(edp_command);
          if (atoi(val) == 1) 
          // 使Led亮 
          digitalWrite(13, HIGH);
          //digitalWrite(8, HIGH);
          else
          digitalWrite(13, LOW);
          // 使Led灭 
          //digitalWrite(8, HIGH);
          if(atoi(val) > 1)
          { 
            sendCommand(0x40); 
            //setting the Write Data Command,using automatic address genuine.
            
            digitalWrite(stbPin, LOW); 
            //pin low. To begin receiving data 
            shiftOut(dioPin, clkPin, LSBFIRST, 0xc0); 
            //Set the start address 0C0H

            
            if(atoi(val) >= 100 && atoi(val) <=1000) 
            {
          shiftOut(dioPin, clkPin, LSBFIRST, digits[0]);
          //thousand data 
          shiftOut(dioPin, clkPin, LSBFIRST, 0x00); 
          //filling high 8- bit data 
          shiftOut(dioPin, clkPin, LSBFIRST, digits[atoi(val)/100%10]); //hundred data 
          shiftOut(dioPin, clkPin, LSBFIRST, 0x00); //filling high 8- bit data 
          shiftOut(dioPin, clkPin, LSBFIRST, digits[atoi(val)/10%10]); //ten data 
          shiftOut(dioPin, clkPin, LSBFIRST, 0x00); //filling high 8- bit data 
          shiftOut(dioPin, clkPin, LSBFIRST, digits[atoi(val)%10]); //bit data 
          shiftOut(dioPin, clkPin, LSBFIRST, 0x00); //filling high 8- bit data
          }
          
          else if(atoi(val) >= 10 && atoi(val) <=100)
          { 
            shiftOut(dioPin, clkPin, LSBFIRST, digits[0]);
            //thousand data 
            shiftOut(dioPin, clkPin, LSBFIRST, 0x00); 
            //filling high 8- bit data 
            shiftOut(dioPin, clkPin, LSBFIRST, digits[0]); //hundred data 
            shiftOut(dioPin, clkPin, LSBFIRST, 0x00); //filling high 8- bit data 
            shiftOut(dioPin, clkPin, LSBFIRST, digits[atoi(val)/10%10]); //ten data 
            shiftOut(dioPin, clkPin, LSBFIRST, 0x00); //filling high 8- bit data 
            shiftOut(dioPin, clkPin, LSBFIRST, digits[atoi(val)%10]); //bit data 
            shiftOut(dioPin, clkPin, LSBFIRST, 0x00); //filling high 8- bit data 
            }
            
            else if(atoi(val) > 0 && atoi(val) <=10)
            { 
              shiftOut(dioPin, clkPin, LSBFIRST, digits[0]);//thousand data 
              shiftOut(dioPin, clkPin, LSBFIRST, 0x00); //filling high 8- bit data 
              shiftOut(dioPin, clkPin, LSBFIRST, digits[0]); //hundred data 
              shiftOut(dioPin, clkPin, LSBFIRST, 0x00); //filling high 8- bit data 
              shiftOut(dioPin, clkPin, LSBFIRST, digits[0]); //ten data 
              shiftOut(dioPin, clkPin, LSBFIRST, 0x00); //filling high 8- bit data 
              shiftOut(dioPin, clkPin, LSBFIRST, digits[atoi(val)%10]); //bit data 
              shiftOut(dioPin, clkPin, LSBFIRST, 0x00); //filling high 8- bit data
              }
              
              digitalWrite(stbPin, HIGH); 
              delay(500);
              }
              //pin high. Stop receiving data 
              packetSend(packetDataSaveTrans(NULL, datastr, val)); //将新数据值上传至数据流 
              break; 
              default:
              ;
              break;
              }
              } 
              }
          
         
           
          if (rcv_pkt.len > 0)
          packetClear(&rcv_pkt);
          delay(150); }
          
          /** readEdpPkt * 从串口缓存中读数据到接收缓存 */
          
