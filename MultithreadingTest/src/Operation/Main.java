package Operation;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.Hashtable;
import java.util.Scanner;
import AboutFile.*;
import Users.*;
import systemUI.*;

public class Main {

	public static Scanner in = new Scanner(System.in);
	public static Hashtable<String, User> users;	
	public static Hashtable<String, Doc> docs;

	public static User search(String name, String password) {
		if (users.containsKey(name)){
			User temp = users.get(name);
			if ((temp.getPassword()).equals(password))
				return temp;
		}
		else {
			System.out.println("用户名或密码错误！");
		}
		return null;
	}

	@SuppressWarnings({ "unchecked" })
	public static void InitUserInfo() throws FileNotFoundException, IOException, DataException, ClassNotFoundException {
		users = new Hashtable<String, User>();		

		ObjectInputStream in = new ObjectInputStream(
				new FileInputStream("userhash.txt"));
		users = (Hashtable<String, User>)in.readObject();
		in.close();

		User user;
		for (String name : users.keySet()) {
			user = users.get(name);
			if(user.getPassword() == null || user.getRole() == null)
				throw new DataException("用户数据格式错误！");
			if(!user.getRole().matches("Administrator|Operator|Browser"))
				throw new DataException("用户数据格式错误！");
		}
	}

	@SuppressWarnings({ "unchecked" })
	public static void InitFileInfo() throws FileNotFoundException, IOException, DataException, ClassNotFoundException {
		docs = new Hashtable<String, Doc>();
		ObjectInputStream in = new ObjectInputStream(
				new FileInputStream("dochash.txt"));
		docs = (Hashtable<String, Doc>)in.readObject();
		in.close();

		Doc doc;
		for(String ID : docs.keySet()) {
			doc = docs.get(ID);
			if(doc.getFilename() == null || doc.getCreator() == null || doc.getTimestamp() == null || doc.getDescription() == null)
				throw new DataException("系统中档案数据格式错误！");
		}
	}

	public static void RebuildUserInfo() {
		User user = new Administrator("AUser", "123", "Administrator");
		users = new Hashtable<String, User>();
		users.put("AUser", user);
		FileOperation.SaveToFile("userhash",users);
	}

	public static void RebuildDocInfo() {
		docs = new Hashtable<String, Doc>();
		FileOperation.SaveToFile("dochash",docs);
	}

	public static void main(String[] args) {

		try {
			InitUserInfo();
		} catch (ClassNotFoundException e) {
			System.out.println("用户数据被改动！重建新数据");
			RebuildUserInfo();
		} catch (FileNotFoundException e) {
			System.out.println("未找到用户信息文件，重建新数据");
			RebuildUserInfo();
		} catch (DataException e) {
			System.out.println(e.getString() + "，重建新数据");
			RebuildUserInfo();
		} catch (IOException e) {
			System.out.println("用户文件信息写入出错，重建新数据");
			RebuildUserInfo();
		}

		try {
			InitFileInfo();
		} catch (ClassNotFoundException e) {
			System.out.println("档案数据被改动！重建新数据");
			RebuildDocInfo();
		} catch (FileNotFoundException e) {
			System.out.println("未找到档案信息文件，重建新数据");
			RebuildDocInfo();
		} catch (DataException e) {
			System.out.println(e.getString() + "，重建新数据");
			RebuildDocInfo();
		} catch (IOException e) {
			System.out.println("档案文件信息写入出错，重建新数据");
			RebuildDocInfo();
		}
		new WelcomeUI();
	}
}
