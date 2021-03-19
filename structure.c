#include "structure.h"

project* selected_project = 0;

project* get_selected_project()
{
    return selected_project;
}

void set_selected_project(project* p)
{
    selected_project = p;
}

channel* get_channel(channel_id channel_id)
{
    return selected_project->channels->o[channel_id];
}

mixer* get_mixer(mixer_id mixer_id)
{
    return selected_project->mixers->o[mixer_id];
}

arrangement* get_arrangement(arrangement_id arrangement_id)
{
    return selected_project->arrangements->o[arrangement_id];
}

track* get_track(track_id track_id)
{
    return selected_project->tracks->o[track_id];
}

timeline* get_timeline(timeline_id timeline_id)
{
    return (get_arrangement(timeline_id.arrangement_id)->timelines)->o[timeline_id.channel_id];
}

track_id create_track(daw_time position)
{
    track* t = msq_malloc(sizeof(*t), 0);
    t->position = position;
    v_append(selected_project->tracks, t);
    return selected_project->tracks->s;
}

void add_track_to_timeline(track_id t, timeline_id timeline_id)
{
    v_append(get_timeline(timeline_id)->tracks, get_track(t));
}

timeline_id add_timeline(channel_id channel, arrangement_id arr)
{
    timeline* t = msq_malloc(sizeof(*t), 0);
    ((arrangement*)selected_project->arrangements->o[arr])->timelines->o[channel] = t;
    return (timeline_id) {channel, arr};
}

mixer_id add_mixer()
{
    mixer* mixer = msq_malloc(sizeof(*mixer), 0);
    v_append(selected_project->mixers, mixer);
    return selected_project->mixers->s - 1;
}

channel_id add_channel()
{
    channel* channel = msq_malloc(sizeof(*channel), 0);
    v_append(selected_project->channels, channel);
    return selected_project->channels->s - 1;
}

void add_channel_to_arrangement(arrangement_id arr, channel_id channel)
{
    v_append(
        selected_project->mixers->o[((arrangement*)selected_project->arrangements->o[arr])->mixer], 
        selected_project->channels->o[channel]);
}

arrangement_id add_arrangement(mixer_id mixer)
{
    arrangement* arrangement = msq_malloc(sizeof(*arrangement),0);
    v_append(selected_project->arrangements, arrangement);
    arrangement->mixer = mixer;
    uint size_of_mixer = get_mixer(arrangement->mixer)->channels->s;
    arrangement->timelines = v_create(size_of_mixer);
    v_fill(arrangement->timelines, 0, 0, size_of_mixer);

    return selected_project->arrangements->s - 1;
}

project* create_empty_project()
{
    project* new_project = msq_malloc(sizeof(*new_project), 0);
    new_project->arrangements = v_create(1);
    new_project->channels = v_create(0);
    new_project->mixers = v_create(1);
    new_project->tracks = v_create(0);
    return new_project;
}

project* create_project(uint number_of_channels)
{
    project* new_project = create_empty_project();
    v_reserve(new_project->channels, number_of_channels);
    return new_project;
}
