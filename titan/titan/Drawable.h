#pragma once

class Drawable {

public:
	virtual int returnID() = 0;
	virtual void deleteBody() = 0;
};