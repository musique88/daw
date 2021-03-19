#include <stdio.h>
#include "structure.h"

int main()
{
    set_selected_project(create_empty_project());
    uint channel1 = add_channel();
    uint mixer = add_mixer();
    uint arrangement = add_arrangement(mixer);
    add_channel_to_arrangement(arrangement, channel1);
    add_timeline(channel1, arrangement);
    
    return 0;
}