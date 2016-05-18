#include "stdafx.h"
#include "CScore.h"




CScore::CScore()
{
	 m_strNO="";
	 m_strName="";
	 m_strClass="";		
	 m_strSex="ÄÐ";
   	 m_fChinese=0;
	 m_fMaths=0;
	 m_fEnglish=0;
	 m_fPhysics=0;
	 m_fChemistry=0;
	 m_fBiology=0;
     m_fSports=0;
}


CScore::~CScore()
{

}


float CScore::fAverage()

{	

	m_fAverage=(m_fChinese+m_fMaths+m_fEnglish+m_fPhysics+m_fChemistry
		+m_fBiology+m_fSports)/7;

	return m_fAverage;
}

float CScore::fScore()
{
		m_fScore=m_fChinese+m_fMaths+m_fEnglish+m_fPhysics+m_fChemistry
					+m_fBiology+m_fSports;
		return m_fScore;
}


