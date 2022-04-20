#ifndef PULSE_H
#define PULSE_H

class Pulse{
  public:
    void fallingTime(unsigned long f);
    int computeTime();
    Pulse(unsigned long r); //constructor

    unsigned long getRising();
    unsigned long getFalling();
    int getTime();

  private:
    unsigned long rising;
    mutable unsigned long falling;

    mutable int time;

};

#endif // !PULSE_H
