//~~ wxBitmap GetClassIcon(const wxString& codingLanguage) [EditIcons] ~~

#include "class_png.h"
#include "c_png.h"
#include "cpp_png.h"
#include "python_png.h"
#include "java_png.h"
#include "php_png.h"

wxMemoryInputStream istream(class_png, sizeof class_png);
wxImage myimage(istream, wxBITMAP_TYPE_PNG);

wxBitmap aBitmap(imageWidth, imageHeight);
wxMemoryDC dc;
dc.SelectObject(aBitmap);
dc.SetBrush(*wxWHITE_BRUSH);

dc.Clear();
dc.DrawBitmap(Scale(myimage), leftBorder, upperBorder, true);

if (codingLanguage == CODE_CPlusPlus)
{
    wxMemoryInputStream istream2(cpp_png, sizeof cpp_png);
    wxImage anImage(istream2, wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(Scale(anImage), leftBorder, upperBorder, true);
}
else if (codingLanguage == CODE_C)
{
    wxMemoryInputStream istream2(c_png, sizeof c_png);
    wxImage anImage(istream2, wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(Scale(anImage), leftBorder, upperBorder, true);
}
else if (codingLanguage == CODE_PYTHON)
{
    wxMemoryInputStream istream2(python_png, sizeof python_png);
    wxImage anImage(istream2, wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(Scale(anImage), leftBorder, upperBorder, true);
}
else if (codingLanguage == CODE_JAVA)
{
    wxMemoryInputStream istream2(java_png, sizeof java_png);
    wxImage anImage(istream2, wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(Scale(anImage), leftBorder, upperBorder, true);
}
else if (codingLanguage == CODE_PHP)
{
    wxMemoryInputStream istream2(php_png, sizeof php_png);
    wxImage anImage(istream2, wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(Scale(anImage), leftBorder, upperBorder, true);
}

return aBitmap;
