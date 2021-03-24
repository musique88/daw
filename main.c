#include <stdio.h>
#include "structure.h"
#include <stdlib.h>

int main()
{
    set_selected_project(create_empty_project());
    uint channel1 = add_channel();
    uint mixer = add_mixer();
    uint arrangement = add_arrangement(mixer);
    add_channel_to_arrangement(arrangement, channel1);
    timeline_id timeline = add_timeline(channel1, arrangement);
    srand(0);
    for(int i = 0; i < 10; i++)
    {
        track_id t = create_track((daw_time){rand()%10, rand()%7, rand()%12}, (daw_time){0,0,0});
        insert_track(timeline, t);
    }

    for (int i = 0; i < 10; i++)
    {
        track* t = get_timeline(timeline)->tracks->o[i];
        printf("%d - %d/%d \n", t->position.mesure, t->position.over, t->position.subdivision);
    }

    return 0;
}