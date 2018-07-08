#include "audioSetter.h"
#include "audioMixer.h"
#include "joystickControler.h"
#include "accelerometerControler.h"
#include "udp.h"

int main(){
    AudioMixer_init();
    audioSetter_init();
    joystick_init();
    udp_init();
    acc_init();
    //makesystem("");
    char* argv="cd mjpg-streamer && ./mjpg_streamer -i \"./input_uvc.so -d /dev/video0 -y -r 320*240\" -o \"./output_http.so -w ./www\"";
    system(argv);
    udp_cleanup();
    AudioMixer_cleanup();
    joystick_cleanup();
    audioSetter_cleanup();
    acc_cleanup();
}
