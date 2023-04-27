#pragma once

template <typename T>
class CResult
{
private :

	bool status_;
	T* value_;

public:

	CResult(bool status);
	CResult(bool status, T* value);
	~CResult();

	bool GetStatus()											{ return status_; }
	T* GetValue()												{ return value_; }

	void SetSatue(bool statue)									{ status_ = statue; }
	void SetValue(int value)									{ value_ = &value; }
	
};

template<typename T>
inline CResult<T>::CResult(bool status)
{
	status_ = status;
}

template<typename T>
inline CResult<T>::CResult(bool status, T* value)
{
	status_ = status;
	value_ = value;
}

template<typename T>
inline CResult<T>::~CResult()
{
}
