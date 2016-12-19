#pragma once
#include "stdafx.h"


static void Curve2CvPoints(double Rad, double centerx, double centery, bool ClockWise, float sangle, float eangle, vector<CvPoint> &m_contourPt)
{
    int nRadius = Rad ;
    //初始化数组来存放转化后的数据
    CvPoint *tmppointer = new CvPoint[361];
    CvPoint *tmppointer1 = new CvPoint[361];
    CFloatPt m_tmpPt;					//将圆弧转化成为直线插入adshape里面
    CvPoint m_CentePoint;
    m_CentePoint.x = centerx ;//太小的时候会造成大误差,圆弧的精度问题
    m_CentePoint.y = centery ;
    CvSize CriSize;
    CriSize.width = CriSize.height = nRadius;
    int tmp_case=0;
    int tmp_num;
    //第一种情况从开始都结束转化，第二种情况从开始到360度，从0到结束
    if (ClockWise)
    {
        if(sangle==360) sangle=0;
        if (sangle<eangle)
            tmp_case = 1;
    }else
    {	
        if(eangle==360)	eangle=0;
        if (sangle>eangle)
            tmp_case = 1;
    }
    //情况一的话就把终点坐标和tmmpointer里面的坐标比，到了就说明结束、
    //情况2的画就分两部分
    //首末两个点要舍弃，因为有可能由于角度的舍弃小数点造成一个像素的误差
    if (tmp_case==1)
    {				
        cvEllipse2Poly(m_CentePoint,CriSize,0,360-sangle,360-eangle,tmppointer,1);//开始到结束一次旋转一度，算出坐标
        tmp_num = abs(int(eangle)-int(sangle));
        int T=m_contourPt.size();
        if(ClockWise)
        {		
            for (int i=1;i<tmp_num;i++)
            {
                m_contourPt.push_back(tmppointer[i]);
            }
        }
        else
        {
            for (int i=tmp_num-1;i>0;i--)
            {
                m_contourPt.push_back(tmppointer[i]);
            }
        }
    }
    else if(tmp_case == 0)
    {								
        cvEllipse2Poly(m_CentePoint,CriSize,0,0,360-(sangle>eangle?sangle:eangle),tmppointer,1);//开始到结束一次旋转一度，算出坐标
        cvEllipse2Poly(m_CentePoint,CriSize,0,360-(sangle<eangle?sangle:eangle),360,tmppointer1,1);//开始到结束一次旋转一度，算出坐标
        int T=m_contourPt.size();
        if(ClockWise)
        {
            tmp_num = sangle<eangle?sangle:eangle;
            for (int i=1;i<tmp_num;i++)
            {
                m_contourPt.push_back(tmppointer1[i]);	
            }

            tmp_num = 360-(sangle>eangle?sangle:eangle);
            for (int i=0;i<tmp_num;i++)
            {
                m_contourPt.push_back(tmppointer[i]);	
            }	
            m_contourPt.insert(m_contourPt.end(),&tmppointer[0],&tmppointer[tmp_num]);
        }
        else
        {
            tmp_num = 360-(sangle>eangle?sangle:eangle);
            for (int i=tmp_num-1;i>=0;i--)
            {
                m_contourPt.push_back(tmppointer[i]);	
            }
            tmp_num = sangle<eangle?sangle:eangle;
            for (int i=tmp_num;i>0;i--)
            {
                m_contourPt.push_back(tmppointer1[i]);	
            }
        }

    }	
    delete []tmppointer;
    tmppointer = NULL;
    delete []tmppointer1;
    tmppointer1 = NULL;
}
static vector<CvPoint> GetRoundedRectPts( IplImage* m_pImg, CvPoint &Center, double nRadius, int nHalfWidth, int nHalfHeight )
{
    CvPoint TTL,TLL,LLB,LBB,RBB,RRB,RRT,RTT;//圆角矩形的8个点
    CvPoint LTCenter,LBCenter,RBCenter,RTCenter;//圆角矩形4个角的圆心

    TTL.x = Center.x - nHalfWidth + nRadius ;   TTL.y = Center.y + nHalfHeight;
    TLL.x = Center.x - nHalfWidth ;             TLL.y = Center.y + nHalfHeight - nRadius;
    LLB.x = Center.x - nHalfWidth ;             LLB.y = Center.y - nHalfHeight + nRadius ;
    LBB.x = Center.x - nHalfWidth + nRadius ;   LBB.y = Center.y - nHalfHeight ;

    RBB.x = Center.x + nHalfWidth - nRadius ;   RBB.y = Center.y - nHalfHeight ;
    RRB.x = Center.x + nHalfWidth ;             RRB.y = Center.y - nHalfHeight + nRadius ;
    RRT.x = Center.x + nHalfWidth ;             RRT.y = Center.y + nHalfHeight - nRadius ;
    RTT.x = Center.x + nHalfWidth - nRadius ;   RTT.y = Center.y + nHalfHeight;
    vector<CvPoint> PtVector;
    RTCenter.x = Center.x + nHalfWidth - nRadius ; RTCenter.y = Center.y + nHalfHeight - nRadius;
    Curve2CvPoints(nRadius,RTCenter.x,RTCenter.y,true,270,360,PtVector);
    RTCenter.x = LBB.x;RTCenter.y = Center.y + nHalfHeight - nRadius;
    Curve2CvPoints(nRadius,RTCenter.x,RTCenter.y,true,180,270,PtVector);
    RTCenter.x = LBB.x;RTCenter.y = Center.y - nHalfHeight + nRadius;
    Curve2CvPoints(nRadius,RTCenter.x,RTCenter.y,true,90,180,PtVector);
    RTCenter.x = Center.x + nHalfWidth - nRadius;RTCenter.y = Center.y - nHalfHeight + nRadius;
    Curve2CvPoints(nRadius,RTCenter.x,RTCenter.y,true,0,90,PtVector);
    cvFillConvexPoly(m_pImg,&PtVector[0],PtVector.size(),cvScalarAll(255));
    return PtVector;
}
//将圆弧转化成opencv的点集


//enlargeFactor表示保留计算的小数点位数,不是cvPoint的话可以考虑使用这个代替上面那个函数
static void Curve2Points(double Rad, double centerx, double centery, bool ClockWise, float sa, float ea, vector<CFloatPt> &m_contourPt,int enlargeFactor)
{
    int nRadius = Rad*enlargeFactor;
    //初始化数组来存放转化后的数据
    CvPoint *tmppointer = new CvPoint[361];
    CvPoint *tmppointer1 = new CvPoint[361];
    CFloatPt m_tmpPt;					//将圆弧转化成为直线插入adshape里面
    CvPoint m_CentePoint;
    m_CentePoint.x = centerx*enlargeFactor;//太小的时候会造成大误差,圆弧的精度问题
    m_CentePoint.y = centery*enlargeFactor;
    CvSize CriSize;
    CriSize.width = CriSize.height = nRadius;
    int tmp_case=0;
    int tmp_num;
    if(sa==360)	sa=0;
    if(ea==360) ea=0;
    //第一种情况从开始都结束，第二种情况从开始到360度，从0到结束
    if (!ClockWise)
    {
        if (ea>sa)
            tmp_case = 1;
    }else
    {	
        if (ea<sa)
            tmp_case = 1;
    }
    //情况一的话就把终点坐标和tmmpointer里面的坐标比，到了就说明结束、
    //情况2的画就分两部分
    //首末两个点要舍弃，因为有可能由于角度的舍弃小数点造成一个像素的误差
    //360 - angle is trans the coordinate System
    if (tmp_case == 1)
    {				
        cvEllipse2Poly(m_CentePoint,CriSize,0,360-sa,360-ea,tmppointer,1);//开始到结束一次旋转一度，算出坐标
        //获取点个数
        tmp_num = abs(int(sa)-int(ea));

        if(ClockWise)
        {		
            for (int i = 1;i<tmp_num;i++)
            {
                m_tmpPt.x = tmppointer[i].x/enlargeFactor;//放大100000倍，缩小回来
                m_tmpPt.y = tmppointer[i].y/enlargeFactor;
                m_contourPt.push_back(m_tmpPt);
            }
        }
        else
        {
            for (int i=tmp_num-1;i>0;i--)
            {
                m_tmpPt.x = tmppointer[i].x/enlargeFactor;//放大100000倍，缩小回来
                m_tmpPt.y = tmppointer[i].y/enlargeFactor;
                m_contourPt.push_back(m_tmpPt);
            }
        }
    }
    else if(tmp_case == 0)
    {								
        cvEllipse2Poly(m_CentePoint,CriSize,0,0,360-(ea>sa?ea:sa),tmppointer,1);//开始到结束一次旋转一度，算出坐标
        cvEllipse2Poly(m_CentePoint,CriSize,0,360-(ea<sa?ea:sa),360,tmppointer1,1);//开始到结束一次旋转一度，算出坐标

        if(ClockWise)
        {
            tmp_num = ea<sa?ea:sa;
            for (int i=1;i<tmp_num;i++)
            {
                m_tmpPt.x = tmppointer1[i].x/enlargeFactor;
                m_tmpPt.y = tmppointer1[i].y/enlargeFactor;
                m_contourPt.push_back(m_tmpPt);	
            }
            tmp_num = 360 - (ea>sa?ea:sa);
            for (int i=0;i<tmp_num;i++)
            {
                m_tmpPt.x = tmppointer[i].x/enlargeFactor;
                m_tmpPt.y = tmppointer[i].y/enlargeFactor;
                m_contourPt.push_back(m_tmpPt);	
            }	
        }
        else
        {
            tmp_num = 360-(ea>sa?ea:sa);
            for (int i=tmp_num-1;i>=0;i--)
            {
                m_tmpPt.x = tmppointer[i].x/enlargeFactor;
                m_tmpPt.y = tmppointer[i].y/enlargeFactor;
                m_contourPt.push_back(m_tmpPt);	
            }
            tmp_num = ea<sa?ea:sa;
            for (int i=tmp_num;i>0;i--)
            {
                m_tmpPt.x = tmppointer1[i].x/enlargeFactor;
                m_tmpPt.y = tmppointer1[i].y/enlargeFactor;
                m_contourPt.push_back(m_tmpPt);	
            }
        }

    }	
    delete []tmppointer;
    tmppointer = NULL;
    delete []tmppointer1;
    tmppointer1 = NULL;
}