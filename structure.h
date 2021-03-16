#include "msqutils/msq.h"

struct track;
struct timeline;
struct channel;
struct mixer;
struct arrangement;
struct project;

struct daw_time{
	uint mesure;
	uint subdivision;
	uint over;
};

struct track{
	struct daw_time position;
};

struct project* get_selected_project();

void set_selected_project(struct project* p);

uint create_track(struct daw_time position);

void add_track_to_timeline(struct track* t, uint arrangement, uint timeline);

struct timeline{
	struct vector* tracks;
};

uint add_timeline(uint mixer);

struct channel{

};

// Returns the index of the channel in the project
uint add_channel();

struct mixer{
    struct vector* channels;
};

// Returns the index of the mixer in the project
uint add_mixer();

void add_channel_to_mixer(uint arrangement, uint mixer, uint channel);

// An arrangement is a mixer with its own timeline
struct arrangement{
    uint mixer;
	struct vector* timelines;
};

uint add_arrangement(uint mixer);

struct project{
	struct vector* channels;
    struct vector* mixers;
    struct vector* arrangements;
	struct vector* tracks;
}; 

struct project* create_empty_project();
struct project* create_project(uint nb_channels);
