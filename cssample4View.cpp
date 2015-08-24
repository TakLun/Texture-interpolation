// cssample4View.cpp : implementation of the CCssample4View class
//

#include "stdafx.h"
#include "cssample4.h"

#include "cssample4Doc.h"
#include "cssample4View.h"

#include <vector>

using namespace std;

vector <int> new_pixels;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCssample4View

IMPLEMENT_DYNCREATE(CCssample4View, CView)

BEGIN_MESSAGE_MAP(CCssample4View, CView)
	//{{AFX_MSG_MAP(CCssample4View)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_TEXTURE_DISABLE, OnViewTextureDisable)
	ON_COMMAND(ID_VIEW_TEXTURE_ENABLE, OnViewTextureEnable)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_ROTATE45DEGREES, &CCssample4View::OnRotate45degrees)
	ON_COMMAND(ID_ENABLEWIREFRAME, &CCssample4View::OnEnablewireframe)
	ON_COMMAND(ID_ROTATEEVERY30DEGREES, &CCssample4View::OnRotateevery30degrees)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCssample4View construction/destruction

CCssample4View::CCssample4View()
{
	m_hDC=NULL;
	m_hRC=NULL;
	w=h=0; //width and height of view area
	m_LButtonDown = false;
	rotate_45_flag = 0;
	wireframe_enable = 0;
	rotate_30 = 0;
	rotate_30_flag = 0;
	start = 0;
/*
	RedSurface[0]= 1.0f; RedSurface[1]=0.0f; RedSurface[2]=0.0f; RedSurface[3]=1.0f;
	GreenSurface[0]= 0.0f; GreenSurface[1]=1.0f; GreenSurface[2]=0.0f; GreenSurface[3]=1.0f;
	BlueSurface[0]= 0.0f; BlueSurface[1]=0.0f; BlueSurface[2]=1.0f; BlueSurface[3]=1.0f;
	BlackSurface[0]= 0.0f; BlackSurface[1]=0.0f; BlackSurface[2]=0.0f; BlackSurface[3]=1.0f;
*/
/*
    rectangle[0].x=250.0;
	rectangle[0].y=100.0;
	rectangle[1].x=634.0;
	rectangle[1].y=100.0;
	rectangle[2].x=634.0;
	rectangle[2].y=356.0;
	rectangle[3].x=250.0;
	rectangle[3].y=356.0;

	triangle1_a.x = 250.0;
	triangle1_a.y = 100.0;
	triangle1_b.x = 634.0;
	triangle1_b.y = 100.0;
	triangle1_c.x = 442.0;
	triangle1_c.y = 228.0;

	triangle2_a.x = 634.0;
	triangle2_a.y = 100.0;
	triangle2_b.x = 634.0;
	triangle2_b.y = 356.0;
	triangle2_c.x = 442.0;
	triangle2_c.y = 228.0;

	triangle3_a.x = 634.0;
	triangle3_a.y = 356.0;
	triangle3_b.x = 250.0;
	triangle3_b.y = 356.0;
	triangle3_c.x = 442.0;
	triangle3_c.y = 228.0;

	triangle4_a.x = 250.0;
	triangle4_a.y = 356.0;
	triangle4_b.x = 250.0;
	triangle4_b.y = 100.0;
	triangle4_c.x = 442.0;
	triangle4_c.y = 228.0;

	m_LDownPos.x = 400.0;
	m_LDownPos.y = 331.0;
	*/

	rectangle[0].x=0.0;
	rectangle[0].y=0.0;
	rectangle[1].x=384.0;
	rectangle[1].y=0.0;
	rectangle[2].x=384.0;
	rectangle[2].y=256.0;
	rectangle[3].x=0.0;
	rectangle[3].y=256.0;

	triangle1_a.x = 0.0;
	triangle1_a.y = 0.0;
	triangle1_b.x = 384.0;
	triangle1_b.y = 0.0;
	triangle1_c.x = 192.0;
	triangle1_c.y = 128.0;

	triangle2_a.x = 384.0;
	triangle2_a.y = 0.0;
	triangle2_b.x = 384.0;
	triangle2_b.y = 256.0;
	triangle2_c.x = 192.0;
	triangle2_c.y = 128.0;

	triangle3_a.x = 384.0;
	triangle3_a.y = 256.0;
	triangle3_b.x = 0.0;
	triangle3_b.y = 256.0;
	triangle3_c.x = 192.0;
	triangle3_c.y = 128.0;

	triangle4_a.x = 0.0;
	triangle4_a.y = 256.0;
	triangle4_b.x = 0.0;
	triangle4_b.y = 0.0;
	triangle4_c.x = 192.0;
	triangle4_c.y = 128.0;

	//m_LDownPos.x = 192.0;
	//m_LDownPos.y = 515.0;
	//m_LDownPos.y = h - ((rectangle[2].y + rectangle[1].y)/2);

}

CCssample4View::~CCssample4View()
{
}

BOOL CCssample4View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCssample4View drawing

void CCssample4View::OnDraw(CDC* pDC)
{
	
	CCssample4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rcClient;
	GetClientRect(rcClient);
	
	w=rcClient.Width();
	h=rcClient.Height();

	wglMakeCurrent(m_hDC,m_hRC);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);		
	
	glColor4f(1.0, 1.0, 1.0, 0.0);

	glViewport(0, 0, (int)(w/1.0), (int)(h/1.0));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, w, 0.0, h);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  
	//glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	
	new_pixels.clear();

	if (start == 0){
		m_LDownPos.x = 192.0;
		m_LDownPos.y = h - ((rectangle[2].y + rectangle[1].y)/2);
		start = 1;
	}

	//rectangle + texture   //// You may rewrite this part for your own implementation
	if (rotate_45_flag == 0){
	glBegin(GL_POLYGON);

		    glTexCoord2f(0.0,0.0);
	    	glVertex3f(0.0+rectangle[0].x,0.0+rectangle[0].y,0.0);
	    	glTexCoord2f(1.0,0.0);
	    	glVertex3f(0.0+rectangle[1].x,0.0+rectangle[1].y,0.0);
	    	glTexCoord2f(1.0,1.0);
		    glVertex3f(0.0+rectangle[2].x,0.0+rectangle[2].y,0.0);
	    	glTexCoord2f(0.0,1.0);
	    	glVertex3f(0.0+rectangle[3].x,0.0+rectangle[3].y,0.0);

    glEnd();
	}

	if (m_LButtonDown == true || rotate_45_flag == 1 || rotate_30_flag == 1 || wireframe_enable == 1){
		if (wireframe_enable == 1) wireframe_enable = 2;
	for (int counter = 0; counter < texImage.bmHeight; ++counter){
		for (int counter2 = 0; counter2 < texImage.bmWidth; ++counter2){

			int real_x_value_start = counter2;
			int real_y_value_start = counter;

			lambda1 = Barycentric_a(triangle1_a.x, triangle1_b.x, m_LDownPos.x, triangle1_a.y, triangle1_b.y, h-m_LDownPos.y, real_x_value_start, real_y_value_start);
			lambda2 = Barycentric_b(triangle1_a.x, triangle1_b.x, m_LDownPos.x, triangle1_a.y, triangle1_b.y, h-m_LDownPos.y, real_x_value_start, real_y_value_start);
			lambda3 = 1 - lambda1 - lambda2;

			if (lambda1 >=0 && lambda1 <=1 && lambda2 >=0 && lambda2 <=1 && lambda3 >=0 && lambda3 <=1){
				triangle_type = 1;
			} else {
				lambda1 = Barycentric_a(triangle2_a.x, triangle2_b.x, m_LDownPos.x, triangle2_a.y, triangle2_b.y, h-m_LDownPos.y, real_x_value_start, real_y_value_start);
				lambda2 = Barycentric_b(triangle2_a.x, triangle2_b.x, m_LDownPos.x, triangle2_a.y, triangle2_b.y, h-m_LDownPos.y, real_x_value_start, real_y_value_start);
				lambda3 = 1 - lambda1 - lambda2;

				if (lambda1 >=0 && lambda1 <=1 && lambda2 >=0 && lambda2 <=1 && lambda3 >=0 && lambda3 <=1){
					triangle_type = 2;
				} else {
					lambda1 = Barycentric_a(triangle3_a.x, triangle3_b.x, m_LDownPos.x, triangle3_a.y, triangle3_b.y, h-m_LDownPos.y, real_x_value_start, real_y_value_start);
					lambda2 = Barycentric_b(triangle3_a.x, triangle3_b.x, m_LDownPos.x, triangle3_a.y, triangle3_b.y, h-m_LDownPos.y, real_x_value_start, real_y_value_start);
					lambda3 = 1 - lambda1 - lambda2;

					if (lambda1 >=0 && lambda1 <=1 && lambda2 >=0 && lambda2 <=1 && lambda3 >=0 && lambda3 <=1){
						triangle_type = 3;
					} else {
						lambda1 = Barycentric_a(triangle4_a.x, triangle4_b.x, m_LDownPos.x, triangle4_a.y, triangle4_b.y, h-m_LDownPos.y, real_x_value_start, real_y_value_start);
						lambda2 = Barycentric_b(triangle4_a.x, triangle4_b.x, m_LDownPos.x, triangle4_a.y, triangle4_b.y, h-m_LDownPos.y, real_x_value_start, real_y_value_start);
						lambda3 = 1 - lambda1 - lambda2;
						
						if (lambda1 >=0 && lambda1 <=1 && lambda2 >=0 && lambda2 <=1 && lambda3 >=0 && lambda3 <=1){
							triangle_type = 4;
						}
					}
				}
			}

			if (triangle_type == 1){
				x_coor_bitmap = (lambda1*rectangle[0].x) + (lambda2*rectangle[1].x) + (lambda3*192);
				y_coor_bitmap = (lambda1*rectangle[0].y) + (lambda2*rectangle[1].y) + (lambda3*128);
			} else if (triangle_type == 2){
				x_coor_bitmap = (lambda1*rectangle[1].x) + (lambda2*rectangle[2].x) + (lambda3*192);
				y_coor_bitmap = (lambda1*rectangle[1].y) + (lambda2*rectangle[2].y) + (lambda3*128);
			} else if (triangle_type == 3){
				x_coor_bitmap = (lambda1*rectangle[2].x) + (lambda2*rectangle[3].x) + (lambda3*192);
				y_coor_bitmap = (lambda1*rectangle[2].y) + (lambda2*rectangle[3].y) + (lambda3*128);
			} else if (triangle_type == 4) {
				x_coor_bitmap = (lambda1*rectangle[3].x) + (lambda2*rectangle[0].x) + (lambda3*192);
				y_coor_bitmap = (lambda1*rectangle[3].y) + (lambda2*rectangle[0].y) + (lambda3*128);
			}

			int width_bitmap = texImage.bmWidth;
			int offset = x_coor_bitmap + width_bitmap * y_coor_bitmap;

			int blue = allPixels[3*offset + 0];
			int green = allPixels[3*offset + 1];
			int red = allPixels[3*offset + 2];

			new_pixels.push_back(red);
			new_pixels.push_back(green);
			new_pixels.push_back(blue);

			glBegin(GL_POINTS);
				glColor3ub(red, green, blue);
				glVertex2d(real_x_value_start, real_y_value_start);
			glEnd();
		}
	}
	}

	if (wireframe_enable == 1 || wireframe_enable == 2){
	glColor4f(1.0, 0.0, 0.0, 0.0);
	glBegin(GL_LINES);
			glVertex2f(rectangle[0].x, rectangle[0].y);
			glVertex2f(m_LDownPos.x, h-m_LDownPos.y);

			glVertex2f(rectangle[1].x, rectangle[1].y);
			glVertex2f(m_LDownPos.x, h-m_LDownPos.y);

			glVertex2f(rectangle[2].x, rectangle[2].y);
			glVertex2f(m_LDownPos.x, h-m_LDownPos.y);

			glVertex2f(rectangle[3].x, rectangle[3].y);  
			glVertex2f(m_LDownPos.x, h-m_LDownPos.y);

	glEnd();
	}

			if (rotate_45_flag == 1){

				glClear(GL_COLOR_BUFFER_BIT);

				int counter5 = 0;

				for (int counter = 0; counter < texImage.bmHeight; ++counter){
					for (int counter2 = 0; counter2 < texImage.bmWidth; ++counter2){

						int real_x = counter2;
						int real_y = counter;

						double radians = 45 * (3.1415926535/180);

						int blue_after_rotate = new_pixels[counter5+2];
						int green_after_rotate = new_pixels[counter5+1];
						int red_after_rotate = new_pixels[counter5];

						int x_rotate = cos(radians) * (real_x - 192) - sin(radians) * (real_y - 128) + 192;
						int y_rotate = sin(radians) * (real_x - 192) + cos(radians) * (real_y - 128) + 128;
						
						glBegin(GL_POINTS);
							glColor3ub(red_after_rotate, green_after_rotate, blue_after_rotate);
							glVertex2d(x_rotate+200, y_rotate+130);
						glEnd();

						counter5+=3;
					}
				}
				rotate_45_flag = 0;
			}

			if (rotate_30_flag == 1){

				glClear(GL_COLOR_BUFFER_BIT);

				int counter5 = 0;

				for (int counter = 0; counter < texImage.bmHeight; ++counter){
					for (int counter2 = 0; counter2 < texImage.bmWidth; ++counter2){

						int real_x = counter2;
						int real_y = counter;

						double radians = rotate_30 * (3.1415926535/180);

						int blue_after_rotate = new_pixels[counter5+2];
						int green_after_rotate = new_pixels[counter5+1];
						int red_after_rotate = new_pixels[counter5];

						int x_rotate = cos(radians) * (real_x - 192) - sin(radians) * (real_y - 128) + 192;
						int y_rotate = sin(radians) * (real_x - 192) + cos(radians) * (real_y - 128) + 128;
						
						glBegin(GL_POINTS);
							glColor3ub(red_after_rotate, green_after_rotate, blue_after_rotate);
							glVertex2d(x_rotate+200, y_rotate+130);
						glEnd();

						counter5+=3;
					}
				}
				rotate_30_flag = 0;
			}
	

	glPopMatrix();
	glFlush();
	glDisable(GL_TEXTURE_2D);

	
//	wglMakeCurrent(m_hDC,NULL);
	wglMakeCurrent(m_hDC,m_hRC);
    ::SwapBuffers(m_hDC);



}

/////////////////////////////////////////////////////////////////////////////
// CCssample4View printing

BOOL CCssample4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CCssample4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{}

void CCssample4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{}

/////////////////////////////////////////////////////////////////////////////
// CCssample4View diagnostics

#ifdef _DEBUG
void CCssample4View::AssertValid() const
{
	CView::AssertValid();
}

void CCssample4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCssample4Doc* CCssample4View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCssample4Doc)));
	return (CCssample4Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCssample4View message handlers

int CCssample4View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	int nPixelFormat;				
	m_hDC = ::GetDC(m_hWnd);			

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	
		1,									
		PFD_DRAW_TO_WINDOW |			
		PFD_SUPPORT_OPENGL |			
		PFD_DOUBLEBUFFER,				
		PFD_TYPE_RGBA, 24, 0, 0, 0, 0, 0, 0,					
		0, 0, 0, 0, 0, 0, 0, 32, 0, 0, 
                PFD_MAIN_PLANE, 0, 0, 0, 0 
	};

    nPixelFormat = ::ChoosePixelFormat(m_hDC, &pfd);
    ::SetPixelFormat(m_hDC, nPixelFormat, &pfd);
    m_hRC = ::wglCreateContext(m_hDC);
    ::wglMakeCurrent(m_hDC,m_hRC);
    SetupGL();
    ::wglMakeCurrent(m_hDC,NULL);
	
	return 0;
}

void CCssample4View::OnDestroy() 
{
	CView::OnDestroy();
	// Clean up rendering context stuff
    ::wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd,m_hDC);	

	free(allPixels);
}

void CCssample4View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
		
    ::wglMakeCurrent(m_hDC,m_hRC);
    SizeGL1(cx, cy);
    ::wglMakeCurrent(NULL,NULL);

}

// Setup GL view/projection matrices for window size.
void CCssample4View::SizeGL1(int w, int h)
{
        // Correct for zero dimensions.
        h = h ? h : 1;
        w = w ? w : 1;
 
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, w, 0, h);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glFlush();
}


void CCssample4View::SetupGL()
{
        glDepthFunc(GL_LEQUAL);
	    glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
}

BOOL CCssample4View::LoadImage(LPCTSTR fileName)
{
	HBITMAP hBmp = (HBITMAP) ::LoadImage (NULL,(LPCTSTR) fileName, 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE |LR_CREATEDIBSECTION);

	if (hBmp == NULL){
		AfxMessageBox("Error: unable to load bitmap file");
        return FALSE;
    }

    // Get bitmap info.
	::GetObject (hBmp, sizeof(texImage), &texImage);

    // Must be 24 bit
    if (texImage.bmBitsPixel != 24){
		AfxMessageBox("Error: bitmap must be 24 bit");
        return FALSE;
    }
        
    glBindTexture(GL_TEXTURE_2D, ImgName);
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, texImage.bmWidth, texImage.bmHeight, 
			GL_BGR_EXT, GL_UNSIGNED_BYTE, texImage.bmBits);   //// texImage.bmBits stores the loaded image

	int file_size = sizeof(unsigned char)*texImage.bmWidth*texImage.bmHeight*3;
	unsigned char *flatPixels = (unsigned char*)texImage.bmBits;
	allPixels = (unsigned char*)malloc(file_size);
	for(int t = 0; t < file_size; t++){
		 allPixels[t] = flatPixels[t];
	}


    return TRUE;
}

/*
void CCssample4View::Render_A_Point(int i, int j){
// “i, j” is the point in the target rectangle
	CPoint c = GeometricInterpolation(i, j);
// “c.x, c.y” is the corresponding pixel in the source image
	int x = c.x;
	int y = c.y;
	int width = texImage.bmWidth;
	int offset = x+width*y; 
	int b = allPixels[3*offset + 0];
	int g = allPixels[3*offset + 1];
	int r = allPixels[3*offset + 2];
	glColor3ub(r, g, b);
	glVertex2d(i, j);
}
*/

void CCssample4View::SetTexture()
{
	glDrawBuffer(GL_BACK);
	glGenTextures(1, &ImgName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	LoadImage("flower.bmp");
}

void CCssample4View::OnViewTextureDisable() 
{
	//your implementation here
	//	
 glDisable(GL_TEXTURE_2D);
 InvalidateRect(NULL);
}

void CCssample4View::OnViewTextureEnable() 
{
	//your implementation here
	//....

 SetTexture();
 glEnable(GL_TEXTURE_2D);
 InvalidateRect(NULL);

}

void CCssample4View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_LButtonDown = true;
}

void CCssample4View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_LButtonDown == true){
		m_LButtonDown = false;
	}
}

void CCssample4View::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_LButtonDown == true)
	{
		m_LDownPos = point;
		InvalidateRect(NULL, FALSE);
	}
	CView::OnMouseMove(nFlags, point);
}

double CCssample4View::Barycentric_a(double x1, double x2, double x3, double y1, double y2, double y3, double x, double y){

	double numerator = ((y2 - y3)*(x - x3)) + ((x3 - x2)*(y - y3));
	double denom = ((y2 - y3)*(x1 - x3)) + ((x3 - x2)*(y1 - y3));
	double lambda_1 = numerator/denom;

	return lambda_1;
}

double CCssample4View::Barycentric_b(double x1, double x2, double x3, double y1, double y2, double y3, double x, double y){

	double numerator = ((y3 - y1)*(x - x3)) + ((x1 - x3)*(y - y3));
	double denom = ((y3 - y1)*(x2 - x3)) + ((x1 - x3)*(y2 - y3));
	double lambda_2 = numerator/denom;

	return lambda_2;
}




void CCssample4View::OnRotate45degrees()
{
	rotate_45_flag = 1;
	InvalidateRect(NULL, FALSE);
}

void CCssample4View::OnEnablewireframe()
{
	wireframe_enable = 1;
	InvalidateRect(NULL, FALSE);
}

void CCssample4View::OnRotateevery30degrees()
{
	rotate_30_flag = 1;
	rotate_30+=30;
	InvalidateRect(NULL, FALSE);
}
