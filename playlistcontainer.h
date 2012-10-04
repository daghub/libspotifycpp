#ifndef PLAYLISTCONTAINER_H
#define PLAYLISTCONTAINER_H

#include "base.h"

NS_SPOTIFY_BEGIN

class playlistcontainer : boost::noncopyable
{
public:
  ~playlistcontainer();

  bool is_loaded() const;

private:
  playlistcontainer(sp_playlistcontainer* pc);

  friend class session;

  sp_playlistcontainer* pc_;
};

NS_SPOTIFY_END

#endif
