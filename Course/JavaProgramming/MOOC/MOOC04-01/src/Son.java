
public class Son extends Father {
	public void hi() {
		//���������չ�Լ��ĳ�Ա����
		System.out.println("hi~~~~~");
	}
	
	public static void main(String[] a)	{
	    Son s = new Son();
	    System.out.println(s.mobile); //Sonû�ж���mobile, ����ͨ������̳е�
	    //System.out.println(s.money); //error �����money��˽�еģ������޷�ֱ�ӷ���
	    s.hello();  //Sonû�ж���f1, ����ͨ������̳е�
	    s.hi();     //Son�����Զ����Լ��ĳ�Ա����
	}
}
