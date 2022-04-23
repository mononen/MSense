#ifndef PULSE_H
#define PULSE_H

class Pulse{
  public:
    void fallingTime(unsigned long f);
    int computeTime();
    Pulse(unsigned long r); //constructor

  private:
    unsigned long rising;
    mutable unsigned long falling;

    mutable unsigned long time;

};

#endif // !PULSE_H