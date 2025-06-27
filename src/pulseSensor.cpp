extern int signal;
extern const int pulse_sensor_pin;


class pulse
{
public:
    int threshold;

    bool foundBeat()
    {
        bool status = true;
        if (signal == 550)
        {
            status = true;
        }
        return status;
    }
};