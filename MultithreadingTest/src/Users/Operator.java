package Users;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import AboutFile.*;
import Operation.*;
public class Operator extends User{

	private static final long serialVersionUID = 1L;

	public Operator(String name, String password, String role) {
		super(name, password, role);
	}

	public void uploadFile(String ID, String sourcefile, String description) throws DataException, FileNotFoundException, IOException {
		if(Main.docs.containsKey(ID)) {
			throw new DataException("该文件ID已存在！");
		}
		else {
			File file = new File(clientpath + sourcefile);
			File tofile = new File(servepath);
			FileOperation.copy(file, tofile);
			java.util.Calendar presenttime = java.util.Calendar.getInstance();    
			Doc doc = new Doc(ID, sourcefile, this.getName(), presenttime, description);
			Main.docs.put(ID, doc);
			FileOperation.SaveToFile("dochash", Main.docs);	
		}
	}
}
