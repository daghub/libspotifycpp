#ifndef ARTIST_H
#define ARTIST_H

#include "base.h"

NS_SPOTIFY_BEGIN

class artist : boost::noncopyable
{
public:
  ~artist();

  const char* name() const;
  bool is_loaded() const;
  const byte* portrait(sp_image_size size);

private:
  artist(sp_artist* artist);

  friend class search;

  sp_artist* artist_;
};


NS_SPOTIFY_END

#endif
