#pragma once
#include "stdafx.h"


static void Curve2CvPoints(double Rad, double centerx, double centery, bool ClockWise, float sangle, float eangle, vector<CvPoint> &m_contourPt)
{
    int nRadius = Rad ;
    //��ʼ�����������ת���������
    CvPoint *tmppointer = new CvPoint[361];
    CvPoint *tmppointer1 = new CvPoint[361];
    CFloatPt m_tmpPt;					//��Բ��ת����Ϊֱ�߲���adshape����
    CvPoint m_CentePoint;
    m_CentePoint.x = centerx ;//̫С��ʱ�����ɴ����,Բ���ľ�������
    m_CentePoint.y = centery ;
    CvSize CriSize;
    CriSize.width = CriSize.height = nRadius;
    int tmp_case=0;
    int tmp_num;
    //��һ������ӿ�ʼ������ת�����ڶ�������ӿ�ʼ��360�ȣ���0������
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
    //���һ�Ļ��Ͱ��յ������tmmpointer���������ȣ����˾�˵��������
    //���2�Ļ��ͷ�������
    //��ĩ������Ҫ��������Ϊ�п������ڽǶȵ�����С�������һ�����ص����
    if (tmp_case==1)
    {				
        cvEllipse2Poly(m_CentePoint,CriSize,0,360-sangle,360-eangle,tmppointer,1);//��ʼ������һ����תһ�ȣ��������
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
        cvEllipse2Poly(m_CentePoint,CriSize,0,0,360-(sangle>eangle?sangle:eangle),tmppointer,1);//��ʼ������һ����תһ�ȣ��������
        cvEllipse2Poly(m_CentePoint,CriSize,0,360-(sangle<eangle?sangle:eangle),360,tmppointer1,1);//��ʼ������һ����תһ�ȣ��������
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
    CvPoint TTL,TLL,LLB,LBB,RBB,RRB,RRT,RTT;//Բ�Ǿ��ε�8����
    CvPoint LTCenter,LBCenter,RBCenter,RTCenter;//Բ�Ǿ���4���ǵ�Բ��

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
//��Բ��ת����opencv�ĵ㼯


//enlargeFactor��ʾ���������С����λ��,����cvPoint�Ļ����Կ���ʹ��������������Ǹ�����
static void Curve2Points(double Rad, double centerx, double centery, bool ClockWise, float sa, float ea, vector<CFloatPt> &m_contourPt,int enlargeFactor)
{
    int nRadius = Rad*enlargeFactor;
    //��ʼ�����������ת���������
    CvPoint *tmppointer = new CvPoint[361];
    CvPoint *tmppointer1 = new CvPoint[361];
    CFloatPt m_tmpPt;					//��Բ��ת����Ϊֱ�߲���adshape����
    CvPoint m_CentePoint;
    m_CentePoint.x = centerx*enlargeFactor;//̫С��ʱ�����ɴ����,Բ���ľ�������
    m_CentePoint.y = centery*enlargeFactor;
    CvSize CriSize;
    CriSize.width = CriSize.height = nRadius;
    int tmp_case=0;
    int tmp_num;
    if(sa==360)	sa=0;
    if(ea==360) ea=0;
    //��һ������ӿ�ʼ���������ڶ�������ӿ�ʼ��360�ȣ���0������
    if (!ClockWise)
    {
        if (ea>sa)
            tmp_case = 1;
    }else
    {	
        if (ea<sa)
            tmp_case = 1;
    }
    //���һ�Ļ��Ͱ��յ������tmmpointer���������ȣ����˾�˵��������
    //���2�Ļ��ͷ�������
    //��ĩ������Ҫ��������Ϊ�п������ڽǶȵ�����С�������һ�����ص����
    //360 - angle is trans the coordinate System
    if (tmp_case == 1)
    {				
        cvEllipse2Poly(m_CentePoint,CriSize,0,360-sa,360-ea,tmppointer,1);//��ʼ������һ����תһ�ȣ��������
        //��ȡ�����
        tmp_num = abs(int(sa)-int(ea));

        if(ClockWise)
        {		
            for (int i = 1;i<tmp_num;i++)
            {
                m_tmpPt.x = tmppointer[i].x/enlargeFactor;//�Ŵ�100000������С����
                m_tmpPt.y = tmppointer[i].y/enlargeFactor;
                m_contourPt.push_back(m_tmpPt);
            }
        }
        else
        {
            for (int i=tmp_num-1;i>0;i--)
            {
                m_tmpPt.x = tmppointer[i].x/enlargeFactor;//�Ŵ�100000������С����
                m_tmpPt.y = tmppointer[i].y/enlargeFactor;
                m_contourPt.push_back(m_tmpPt);
            }
        }
    }
    else if(tmp_case == 0)
    {								
        cvEllipse2Poly(m_CentePoint,CriSize,0,0,360-(ea>sa?ea:sa),tmppointer,1);//��ʼ������һ����תһ�ȣ��������
        cvEllipse2Poly(m_CentePoint,CriSize,0,360-(ea<sa?ea:sa),360,tmppointer1,1);//��ʼ������һ����תһ�ȣ��������

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