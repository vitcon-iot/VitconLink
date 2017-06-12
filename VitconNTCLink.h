/**
 * Created by Park, Nil on 2016-06-29.
 * Last Revision: 2017-04-27
 *
 * 본 모듈은 NTC-LINK를 위한 라이브러리이다.
 * 타겟 NTC 제품은 NTC-10KD-5J이며 기본 Load 저항은 1K이다.
 * 다만 이 값은 변경 가능하다.
 *
 * Park, Nil (2017-04-27): Vitcon Namespace 추가
 */

#ifndef VITCON_NTCLINK_H_
#define VITCON_NTCLINK_H_

namespace vitcon
{
  class NTCLink
  {
  private:
    static const float MAXADC = 1023.0;
    static const float ABS_ZERO = -273.15;
    static const int AVG_COUNT = 20;
    // Moving Average
    int mSamples[AVG_COUNT];
    int mIndex;
    bool mIsFirst;
    // Coefficients
    float mT0; // nominal temperature of NTC sensor
    float mR0; // nominal resistance of NTC sensor
    float mR1; // load resistance
    float mB; // coefficient of NTC sensor
    // Init function
    void Init(float t0, float r0, float r1, float b);
  public:
    NTCLink();
    NTCLink(float t0, float r0, float b);
    NTCLink(float t0, float r0, float r1, float b);
    float GetTemperature(int adc);
  };
}

#endif /* VITCON_NTCLink_H_ */
