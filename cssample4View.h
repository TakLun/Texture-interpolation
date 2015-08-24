// cssample4View.h : interface of the CCssample4View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSsample4VIEW_H__72070A70_2B2E_4625_A38B_3C3967F61AFB__INCLUDED_)
#define AFX_CSsample4VIEW_H__72070A70_2B2E_4625_A38B_3C3967F61AFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCssample4View : public CView
{
protected: // create from serialization only
	CCssample4View();
	DECLARE_DYNCREATE(CCssample4View)

// Attributes
public:
	CCssample4Doc* GetDocument();

// Operations
public:

	int m_GLPixelIndex;	
	HDC m_hDC;
	HGLRC m_hRC;

	CPoint m_LDownPos;
	BOOL m_LButtonDown;

	CPoint rectangle[4];

	unsigned char *allPixels;

	int w, h, triangle_type, x_coor_bitmap, y_coor_bitmap, rotate_45_flag, wireframe_enable, rotate_30_flag, rotate_30;

	int start;

	double lambda1, lambda2, lambda3;

	CPoint triangle1_a, triangle1_b, triangle1_c;
	CPoint triangle2_a, triangle2_b, triangle2_c;
	CPoint triangle3_a, triangle3_b, triangle3_c;
	CPoint triangle4_a, triangle4_b, triangle4_c;

	GLfloat RedSurface[4];
	GLfloat GreenSurface[4];
	GLfloat YellowSurface[4];
	GLfloat WhiteSurface[4];
	GLfloat BlueSurface[4];
	GLfloat BlackSurface[4];
	
	// Setup GL view/projection matrices for window size.
    void SizeGL1(int w, int h);
    // Setup default params (lighting, etc...) for GL.
    void SetupGL();
    // Render scene using OpenGL.

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCssample4View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetTexture();
	GLuint ImgName;
	BITMAP texImage;//// storing the loaded image
	BITMAP texImagw2;
	BOOL LoadImage(LPCTSTR fileName);
	virtual ~CCssample4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCssample4View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewTextureDisable();
	afx_msg void OnViewTextureEnable();
	afx_msg void Render_A_Point(int i, int j);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg double Barycentric_b(double x1, double x2, double x3, double y1, double y2, double y3, double x, double y);
	afx_msg double Barycentric_a(double x1, double x2, double x3, double y1, double y2, double y3, double x, double y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRotate45degrees();
	afx_msg void OnEnablewireframe();
	afx_msg void OnRotateevery30degrees();
};

#ifndef _DEBUG  // debug version in cssample4View.cpp
inline CCssample4Doc* CCssample4View::GetDocument()
   { return (CCssample4Doc*)m_pDocument; }
#endif


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSsample4VIEW_H__72070A70_2B2E_4625_A38B_3C3967F61AFB__INCLUDED_)
