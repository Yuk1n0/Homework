package systemUI;

import java.awt.Color;
import javax.swing.JButton;

import Users.*;

public class AdministratorUI extends UserUI {

	private static final long serialVersionUID = 1L;

	public AdministratorUI(User user) {
		super(user);
		usermanage = new JButton("用户管理");
		usermanage.setBackground(Color.white);
		usermanage.setFont(font);
		usermanage.addActionListener(this);
		jp.removeAll();
		jp.add(menu);
		jp.add(usermanage);
		jp.add(filemanage);
		jp.add(changepass);
		jp.add(exit);
	}
}