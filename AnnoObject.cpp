#include <mem.h>
#include "AnnoObject.h"
#include <math.h>

AnnoObject::AnnoObject( void* mem, UINT len, AnsiString type )
: _mem(0), _len(len), myType(type), myTreeNode(0), myParentNode(0)
{
    if(len > 0) {
        _mem = new BYTE[len];
        memcpy( _mem, mem, len );
    }
}

TColor AnnoObject::colors[8] = {clRed, clBlue, clYellow,
        clWhite, clPurple, clBlack, clMaroon, clGreen };

AnnoObject::~AnnoObject()
{
    delete [] _mem;
}

TTreeNode* AnnoObject::getCategoryNode( TTreeView* tree )
{
    int i;
    for( i=0; i<tree->Items->Count; i++ )
    {
        if( tree->Items->Item[i]->Text == myCategory )
            return tree->Items->Item[i];
    }

    TTreeNode* node = tree->Items->Add( 0, myCategory );
    return node;
}

void AnnoObject::addToTree(TTreeView* tree)
{
    myTreeNode =
        tree->Items->AddChild( getCategoryNode(tree), getName() );
    myTreeNode->Data = this;
    myTreeNode->ImageIndex = getImageIndex();
    myTreeNode->SelectedIndex = myTreeNode->ImageIndex;
}

AnsiString AnnoObject::getName(void) const
{
    return "Unbekannt";
}

void AnnoObject::select(TCanvas* canvas) const
{
    canvas->Pen->Color = clWhite;
    canvas->Pen->Width = 2;
    canvas->Rectangle( boundingBox() );
}

void AnnoObject::highlight(TCanvas* canvas) const
{
    canvas->Pen->Color = clBlack;
    canvas->Pen->Width = 1;
    canvas->Rectangle( boundingBox() );
}

TRect AnnoObject::boundingBox(void) const
{
    return TRect();
}

bool AnnoObject::containsPoint(TPoint p) const
{
    TRect r( boundingBox() );
    return  p.x >= r.left && p.x < r.right &&
            p.y >= r.top  && p.y < r.bottom;
}

TTreeNode* AnnoObject::getTreeNode(void)
{
    return myTreeNode;
}

void AnnoObject::paint( TCanvas* canvas )
{
}

TImageIndex AnnoObject::getImageIndex() const
{
    return 0;
}

bool AnnoObject::renameAllowed() const
{
    return false;
}

void AnnoObject::rename(const AnsiString& newName)
{
}

void AnnoObject::exportToFile(TFileStream* tfs) const
{
}


double AnnoObject::getDistanceFrom(TPoint p) const
{
    TPoint c = getCenter();
    double a = (double)(c.x - p.x);
    double b = (double)(c.y - p.y);
    return sqrt(a*a + b*b);
}

TPoint AnnoObject::getCenter() const
{
    TRect r(boundingBox());
    return TPoint(r.left + (r.right-r.left)/2,
                  r.top + (r.bottom-r.top)/2);

}

UINT AnnoObject::getRadius() const
{
    TRect r(boundingBox());
    return (r.Width() > r.Height()) ? r.Width()/2 : r.Height()/2;
}


void __fastcall AnnoObject::setHighlight(bool value)
{
        myHighlight = value;
}
bool __fastcall AnnoObject::getHighlight()
{
    return myHighlight;
}
