//******************************************************
//** Coding is done with Astade Quick and Dirty Coder **
//** Filename: AdeModelElement.h                      **
//******************************************************

#ifndef ADEMODELELEMENT_H
#define ADEMODELELEMENT_H


class AdeModelElement
{
	public:
		AdeModelElement();
		~AdeModelElement();
	int	Type();
	void	Delete();

	protected:
	wxString	GetFeature();

	private:
	wxFileName	myFileName;
};

#endif
