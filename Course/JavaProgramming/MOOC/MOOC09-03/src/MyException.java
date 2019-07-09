public class MyException extends Exception {

	private String returnCode ;  //�쳣��Ӧ�ķ�����
	private String returnMsg;  //�쳣��Ӧ��������Ϣ
	
	public MyException() {
		super();
	}

	public MyException(String returnMsg) {
		super(returnMsg);
		this.returnMsg = returnMsg;
	}

	public MyException(String returnCode, String returnMsg) {
		super();
		this.returnCode = returnCode;
		this.returnMsg = returnMsg;
	}

	public String getReturnCode() {
		return returnCode;
	}

	public String getreturnMsg() {
		return returnMsg;
	}
}