package Users;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.Serializable;

import Operation.DataException;
import Operation.Main;
import AboutFile.FileOperation;

public abstract class User implements Serializable{

	private static final long serialVersionUID = 1L;

	private String name;
	private String password;
	private String role;

	String servepath = "e://";
	String clientpath = "d://";

	public User(String name, String password, String role) {
		this.name = name;
		this.password = password;
		this.role = role;
	}

	public void changeSelfInfo(String password, String newpassword, String sure) throws DataException {

		if(password.equals(this.password)) {
			if(newpassword.equals(sure)) {
				this.password = newpassword;
				FileOperation.SaveToFile("userhash",Main.users);
			}
			else
				throw new DataException("确认新密码错误！");
		}
		else
			throw new DataException("密码错误！");
	}

	public String[][] FileTable() {
		String[][] list = new String[Main.docs.size()][5];
		int i = 0;
		for(String ID : Main.docs.keySet()) {
			list[i][0] = Main.docs.get(ID).getID();
			list[i][1] = Main.docs.get(ID).getFilename();
			list[i][2] = Main.docs.get(ID).getCreator();
			java.text.SimpleDateFormat f =new java.text.SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			list[i][3] = f.format(Main.docs.get(ID).getTimestamp().getTime());
			list[i][4] = Main.docs.get(ID).getDescription();
			i++;
		}
		return list;
	}

	public void downloadFile(String ID) throws DataException, FileNotFoundException, IOException {

		if(!Main.docs.containsKey(ID)) {
			throw new DataException("无该ID") ;
		}
		String sourcefile = Main.docs.get(ID).getFilename();

		File file = new File(servepath + sourcefile);
		File tofile = new File(clientpath);

		FileOperation.copy(file, tofile);
	}

	@Override
	public String toString() {
		return "User [name=" + name + ", password=" + password + ", role=" + role + ", servepath=" + servepath
				+ ", clientpath=" + clientpath + "]";
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getRole() {
		return role;
	}

	public void setRole(String role) {
		this.role = role;
	}
}
