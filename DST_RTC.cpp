/*
    Function to figure out if we're in Daylight Saving Time, then adding an hour if we are in DST.
    adapted from nseidle
    https://github.com/nseidle/Daylight_Savings_Time_Example/blob/master/Daylight_Savings_Time_Example.ino
    This algorithm is programmed to observe Daylight Saving Time in the United States, where as of the time of writing  DST is observed
    between the second Sunday in March and the first Sunday in November. The rules for DST vary by country and territory.
    https://en.wikipedia.org/wiki/Daylight_saving_time_by_country
    If you're in a territory which observes DST differently this code will need to be modified. If you're lucky enough to not observe DST
    then much of this code can be commented out!
    This method doesn't check whether its 2am or not when the time change officially occurs. This could be more accurate at the expense of being more complicated.
*/

#include "Arduino.h"
#include "DST_RTC.h"

DST_RTC::DST_RTC()
{

}

boolean DST_RTC::checkDST(DateTime RTCTime)
{
  //DateTime RTCTime = rtc.now();

  //Get the day of the week. 0 = Sunday, 6 = Saturday
  int previousSunday = RTCTime.day() - RTCTime.dayOfTheWeek();
  int nextSunday = RTCTime.day() + (7 - RTCTime.dayOfTheWeek());

  boolean dst = false; //Assume we're not in DST
  if (RTCTime.month() > 3 && RTCTime.month() < 11) dst = true; //DST is happening!

  //In March, we are DST if our previous Sunday was on or after the 8th.
  if (RTCTime.month() == 3)
  {
    //if (previousSunday >= 8) dst = true;
    if (nextSunday > 31) dst = true;
  }
  //In November we must be before the first Sunday to be dst.
  //That means the previous Sunday must be before the 1st.
  if (RTCTime.month() == 10)
  {
    //if (previousSunday <= 0) dst = true;
    if (nextSunday <= 31) dst = true;
  }

return dst;
}

DateTime DST_RTC::calculateTime(DateTime RTCTime)
{
  //DateTime RTCTime = rtc.now();
    if (checkDST(RTCTime) == true) {
      RTCTime = RTCTime.unixtime() + 3600;  // add 1 hour or 3600 seconds to the time
    }
  return RTCTime;
}
