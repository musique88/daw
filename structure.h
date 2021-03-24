#include "msqutils/msq.h"

typedef uint track_id;
typedef uint arrangement_id;
typedef uint mixer_id;
typedef uint channel_id;
typedef struct {channel_id channel_id; arrangement_id arrangement_id;} timeline_id;

typedef struct{
	uint mesure;
	uint subdivision;
	uint over;
} daw_time;

typedef struct {
	daw_time position;
	daw_time duration;
} track;

// One timeline is an ordered vector of tracks
// in order of appearance for precalculating samples
//
// Timelines tracks should only be modified via insert_track()
typedef struct{
	vector* tracks;
} timeline;

typedef struct{

} channel;

typedef struct {
    vector* channels;
} mixer;

typedef struct{
    mixer_id mixer;
	vector* timelines;
} arrangement;

typedef struct{
	vector* channels;
    vector* mixers;
    vector* arrangements;
	vector* tracks;
} project; 

project* get_selected_project();

void set_selected_project(project* p);

channel* get_channel(channel_id channel_id);

mixer* get_mixer(mixer_id mixer_id);

arrangement* get_arrangement(arrangement_id arrangement_id);

track* get_track(track_id track_id);

timeline* get_timeline(timeline_id timeline_id);

track_id create_track(daw_time position, daw_time duration);

void insert_track(timeline_id timeline_id, track_id track_id);

//void add_track_to_timeline(track_id t, timeline_id timeline_id);

timeline_id add_timeline(uint channel, uint arrangement);

// Returns the index of the channel in the project
channel_id add_channel();

// Returns the index of the mixer in the project
mixer_id add_mixer();

void add_channel_to_arrangement(uint arrangement, uint channel);

arrangement_id add_arrangement(uint mixer);

project* create_empty_project(); 
project* create_project(uint nb_channels);
