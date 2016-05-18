class CScore
{
public:
	CScore();
	~CScore();
	float fScore();
	float fAverage();
public:
	
	CString m_strNO;
	CString m_strName;
	CString m_strClass;
	CString	m_strSex;
	float	m_fChinese;
	float	m_fMaths;
	float	m_fEnglish;
	float	m_fPhysics;
	float	m_fChemistry;
	float   m_fBiology;
	float   m_fSports;

private:
	float	m_fScore;
	float   m_fAverage;





};