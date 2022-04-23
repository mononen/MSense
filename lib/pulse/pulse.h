#ifndef PULSE_H
#define PULSE_H

class Pulse{
  public:
    void setFalling(unsigned long f);
    void setFallingEnd(unsigned long f);
    int computeTime();
    unsigned long getRising();
    unsigned long getFalling();
    unsigned long getFallingEnd();
    int getTime();
    Pulse(unsigned long r); //constructor

  private:
    unsigned long rising;
    mutable unsigned long falling;
    mutable unsigned long fallingEnd;

    int time;

};

#endif // !PULSE_H