#ifndef TRACK_H
#define TRACK_H

#include "base.h"

NS_SPOTIFY_BEGIN

class track : boost::noncopyable
{
public:
  ~track();

  bool is_loaded() const;
  const char* name() const;

  /*sig::signal< void(sp_playlist*, int position) > added;
  sig::signal< void(sp_playlist*, int position) > removed;
  sig::signal< void(sp_playlist*, int position, int new_position) > moved;
  sig::signal< void() > loaded; */

private:
  track(sp_track* track);

  /* static void SP_CALLCONV cb_playlist_added(sp_playlistcontainer* pc, sp_playlist* playlist, */
  /*                                           int position, void *userdata); */

  friend class playlist;

  sp_track* track_;
};

NS_SPOTIFY_END

#endif
