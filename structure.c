#include "structure.h"

struct project* selected_project = 0;

struct project* get_selected_project()
{
    return selected_project;
}

void set_selected_project(struct project* p)
{
    selected_project = p;
}

uint create_track(struct daw_time position)
{
    struct track* t = msq_malloc(sizeof(*t), 0);
    t->position = position;
    v_append(selected_project->tracks, t);
    return selected_project->tracks->s;
}

void add_track_to_timeline(struct track* t, uint arrangement, uint timeline)
{
    // selected the right timeline to put in the track
    struct timeline* selected_timeline = ((struct arrangement*)selected_project->arrangements->o[arrangement])->timelines->o[timeline];
    v_append(selected_timeline->tracks,t);
}

uint add_timeline(uint mixer)
{
    struct arrangement* a = msq_malloc(sizeof(*a), 0);
    v_append(selected_project->arrangements, a);
    a->timelines = v_create(((struct mixer*)selected_project->mixers->o[mixer])->channels->s);
    return selected_project->arrangements->s - 1;
}

uint add_mixer()
{
    struct mixer* mixer = msq_malloc(sizeof(*mixer), 0);
    v_append(selected_project->mixers, mixer);
    return selected_project->mixers->s - 1;
}

uint add_channel()
{
    struct channel* channel = msq_malloc(sizeof(*channel), 0);
    v_append(selected_project->channels, channel);
    return selected_project->channels->s - 1;
}

void add_channel_to_mixer(uint arrangement, uint mixer, uint channel)
{
    ((struct arrangement*)selected_project->arrangements->o[arrangement])->mixer = mixer;
    v_append(selected_project->mixers, selected_project->channels->o[channel]);
}

uint add_arrangement(uint mixer)
{
    struct arrangement* arrangement = msq_malloc(sizeof(*arrangement),0);
    v_append(selected_project->arrangements, arrangement);
    arrangement->mixer = mixer;
    return selected_project->arrangements->s - 1;
}

struct project* create_empty_project()
{
    struct project* new_project = msq_malloc(sizeof(*new_project), 0);
    new_project->arrangements = v_create(1);
    new_project->channels = v_create(0);
    new_project->mixers = v_create(1);
    new_project->tracks = v_create(0);
    return new_project;
}

struct project* create_project(uint number_of_channels)
{
    struct project* new_project = create_empty_project();
    v_reserve(new_project->channels, number_of_channels);
    return new_project;
}
