#ifndef __AnnoObject_h__
#define __AnnoObject_h__

#include <vcl\comctrls.hpp>
#pragma hdrstop

#include "Anno1602Read.h"

class AnnoObject
{
public:
    AnnoObject( void* mem, UINT len, AnsiString type );
    virtual ~AnnoObject();
    void addToTree(TTreeView* tree);
    virtual void paint(TCanvas* canvas);
    virtual void select(TCanvas* canvas) const;
    virtual TRect boundingBox(void) const;
    virtual bool containsPoint(TPoint p) const;
    virtual AnsiString getName(void) const;
    TTreeNode* getTreeNode(void);
    AnsiString inline getType(void) const;
    virtual TImageIndex getImageIndex() const;
    virtual bool renameAllowed() const;
    virtual void rename(const AnsiString& newName);
    virtual void exportToFile(TFileStream* tfs) const;
    virtual double getDistanceFrom(TPoint p) const;
    virtual TPoint getCenter() const;
    UINT getRadius() const;
    virtual void highlight(TCanvas*) const;
    void __fastcall setHighlight(bool value);
    bool __fastcall getHighlight();

protected:
    void* _mem;
    UINT _len;
    AnsiString myCategory;
    TTreeNode* getCategoryNode( TTreeView* tree );
    static TColor colors[8];

private:
    AnsiString myType;
    TTreeNode* myTreeNode;
    TTreeNode* myParentNode;
    bool myHighlight;
};


AnsiString inline AnnoObject::getType(void) const
{
    return myType;
}

#endif



