#define SDL_BlitSurface SDL_BlitSurface

int SDL_BlitSurface(SDL_Surface *surface, SDL_Rect *source, SDL_Surface *support, SDL_Rect *position)
{
	static SDL_Rect newSrc;
	static SDL_Rect newPosition;

	if(position->x < 0 || position->y < 0)
	{	
     	if(position->x < 0 && source != NULL)newSrc.x = source->x-position->x;
		else if(position->x < 0 && source == NULL)newSrc.x = -position->x;
		else if(source != NULL)newSrc.x = source->x;
		else newSrc.x = 0;

		if(position->y < 0 && source != NULL)newSrc.y = source->y-position->y;
		else if(position->y < 0 && source == NULL)newSrc.y = -position->y;
		else if(source != NULL)newSrc.y = source->y;
		else newSrc.y = 0;

		if(source == NULL)
		{
			newSrc.w = surface->w;
			newSrc.h = surface->h;
		}
		else
		{
			if(position->x < 0)newSrc.w = source->w + position->x;
			else newSrc.w = source->w;
			if(position->y < 0)newSrc.h = source->h + position->y;
			else newSrc.h = source->h;
		}

		if((source != NULL && newSrc.x < (source->x+source->w) && newSrc.y < (source->y+source->h))
		|| (source == NULL && newSrc.x < surface->w && newSrc.y < surface->h))
		{
			if(position->x < 0)newPosition.x = 0;
			else newPosition.x = position->x;
			if(position->y < 0)newPosition.y = 0;
			else newPosition.y = position->y;
	
			return SDL_UpperBlit(surface, &newSrc, support, &newPosition);
		}
	}
	else
	{
   		return SDL_UpperBlit(surface, source, support, position);
	}
}
