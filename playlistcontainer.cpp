#include "playlistcontainer.h"

NS_SPOTIFY_BEGIN

playlistcontainer::playlistcontainer(sp_playlistcontainer* pc) : pc_(pc)
{
  sp_playlistcontainer_add_ref(pc_);
}

playlistcontainer::~playlistcontainer()
{
  sp_playlistcontainer_release(pc_);
}

bool playlistcontainer::is_loaded() const
{
  return sp_playlistcontainer_is_loaded(pc_);
}

NS_SPOTIFY_END

