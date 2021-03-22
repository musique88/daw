#include <stdio.h>
#include "structure.h"

int main()
{
    set_selected_project(create_empty_project());
    uint channel1 = add_channel();
    uint channel2 = add_channel();
    uint mixer = add_mixer();
    uint mixer2 = add_mixer();
    uint arrangement = add_arrangement(mixer2);
    add_channel_to_arrangement(arrangement, channel1);
    add_channel_to_arrangement(arrangement, channel2);
    timeline_id timeline = add_timeline(channel1, arrangement);
    printf("%d - %d - %d\n", timeline.arrangement_id, timeline.channel_id, get_timeline(timeline)->tracks->s);
    printf("%d \n", mixer2);
    
    return 0;
}