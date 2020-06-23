package Users;

import AboutFile.FileOperation;
import Operation.*;

public class Administrator extends User{

	private static final long serialVersionUID = 1L;

	public Administrator(String name, String password, String role) {
		super(name, password, role);
	}

	public void changeRole(User changing, String newrole) {
		changing.setRole(newrole);
		Main.users.put(changing.getName(), changing);
		FileOperation.SaveToFile("userhash",Main.users);				
	}

	public void addUser(String name, String password, String role) throws DataException {
		User user;
		if (Main.users.containsKey(name))
			throw new DataException("用户名已存在！"); 
		else {
			if (role.equals("Administrator")) 
				user = new Administrator(name, password, "Administrator"); 
			else if (role.equals("Operator")) 
				user = new Operator(name, password, "Operator"); 
			else
				user = new Browser(name, password, "Browser");
			Main.users.put(name, user);
			FileOperation.SaveToFile("userhash",Main.users);
		}
	}

	public void delUser(String name) throws DataException {
		if (!name.equals("boss"))
		{
			Main.users.remove(name);
			FileOperation.SaveToFile("userhash",Main.users);
		}
		else if (name.equals("boss")) {
			throw new DataException("最大BOSS无法删除！");
		}
		else if (name.equals(this.getName())) {
			throw new DataException("无法删除自己！");
		}
	}

	public String[][] InitTable(){
		String[][] list = new String[Main.users.size()][2];
		int i = 0;
		for(String name : Main.users.keySet()) {
			list[i][0] = Main.users.get(name).getName();
			list[i][1] = Main.users.get(name).getRole();
			i++;
		}
		return list;
	}
}
