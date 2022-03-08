	
// [SEARCH]
PyObject* netSendExchangeStartPacket(PyObject* poSelf, PyObject* poArgs)
// [ADD UNDER AS NEW FUNCTION]
PyObject* netSendDiceStartPacket(PyObject* poSelf, PyObject* poArgs)
{
	int vid;
	if (!PyTuple_GetInteger(poArgs, 0, &vid))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendDiceStartPacket(vid);
	return Py_BuildNone();
}

// [SEARCH]
	{ "SendExchangeStartPacket",			netSendExchangeStartPacket,				METH_VARARGS },
// [ADD UNDER]
	{ "SendDiceStartPacket",				netSendDiceStartPacket,				METH_VARARGS },
