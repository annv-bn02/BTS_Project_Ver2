/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_BTS_Frame_Message_Update_Sensor(void);
extern void test_BTS_Frame_Message_Update_Device(void);
extern void test_BTS_Frame_Message_Control1_Device_Lamp(void);
extern void test_BTS_Frame_Message_Control1_Device_Fan(void);
extern void test_BTS_Frame_Message_Control1_Device_Conditioner(void);
extern void test_BTS_Frame_Message_Control2_Device_Lamp(void);
extern void test_BTS_Frame_Message_Control2_Device_Fan(void);
extern void test_BTS_Frame_Message_Control2_Device_Conditioner(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_bts_frame_message.c");
  run_test(test_BTS_Frame_Message_Update_Sensor, "test_BTS_Frame_Message_Update_Sensor", 12);
  run_test(test_BTS_Frame_Message_Update_Device, "test_BTS_Frame_Message_Update_Device", 79);
  run_test(test_BTS_Frame_Message_Control1_Device_Lamp, "test_BTS_Frame_Message_Control1_Device_Lamp", 141);
  run_test(test_BTS_Frame_Message_Control1_Device_Fan, "test_BTS_Frame_Message_Control1_Device_Fan", 194);
  run_test(test_BTS_Frame_Message_Control1_Device_Conditioner, "test_BTS_Frame_Message_Control1_Device_Conditioner", 247);
  run_test(test_BTS_Frame_Message_Control2_Device_Lamp, "test_BTS_Frame_Message_Control2_Device_Lamp", 300);
  run_test(test_BTS_Frame_Message_Control2_Device_Fan, "test_BTS_Frame_Message_Control2_Device_Fan", 353);
  run_test(test_BTS_Frame_Message_Control2_Device_Conditioner, "test_BTS_Frame_Message_Control2_Device_Conditioner", 406);

  return UnityEnd();
}
