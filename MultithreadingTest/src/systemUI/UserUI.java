package systemUI;

import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import Users.*;

public class UserUI extends JFrame implements ActionListener{

	private static final long serialVersionUID = 1L;

	protected User user;
	protected JButton usermanage, filemanage, changepass, exit;
	protected JLabel username, welcome, menu, timelabel;
	protected Font font;
	protected JMenuBar menuBar = new JMenuBar();
	protected JPanel jp = new JPanel(), title = new JPanel();
	protected String time = null;

	public UserUI(User user) {
		this.user = user;
		username = new JLabel(user.getName(),SwingUtilities.RIGHT);
		font = new Font("宋体",Font.BOLD,72);
		username.setFont(font);
		username.setForeground(Color.BLACK);
		welcome = new JLabel("",SwingUtilities.CENTER);
		font = new Font("宋体",Font.BOLD,56);
		welcome.setFont(font);

		title.setLayout(new GridLayout(1, 2));
		title.add(username);

		font = new Font("宋体", Font.BOLD, 48);
		menu = new JLabel("菜单", SwingUtilities.CENTER);
		menu.setFont(font); menu.setForeground(Color.BLACK);

		jp.setLayout(new GridLayout(5, 1));
		jp.setBorder(BorderFactory.createEmptyBorder(0, 160, 100, 160));
		jp.add(menu);
		this.add(jp);
		font = new Font("宋体", Font.PLAIN, 36);

		filemanage = new JButton("文件管理");
		changepass = new JButton("修改密码");
		exit = new JButton("返回");
		filemanage.setBackground(Color.white);
		filemanage.setFont(font);
		filemanage.addActionListener(this);
		changepass.setBackground(Color.white);
		changepass.setFont(font);
		changepass.addActionListener(this);
		exit.setBackground(Color.white);
		exit.setFont(font);
		exit.addActionListener(this);
		jp.add(filemanage);
		jp.add(changepass);
		jp.add(exit);

		this.setTitle(user.getRole());
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(740, 760);
		this.setVisible(true);
		this.setResizable(false);
		this.setLocationRelativeTo(null);
	}

	public String getTime() {
		Calendar calendar = Calendar.getInstance();
		Date date = (Date) calendar.getTime();
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		time = format.format(date);
		return time;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == filemanage) {
			this.setVisible(false);
			if(user.getRole().equals("Operator")) {
				new OperatorFileList((Operator) user);
			}
			else {
				new FileListUI(user);
			}
		}
		if(e.getSource() == changepass) {
			new changePasswordUI(user);
		}
		if(e.getSource() == exit) {
			this.dispose();
			new SignIn();
		}
		if(e.getSource() == usermanage) {
			this.setVisible(false);
			new UserListUI((Administrator)user);
		}
	}
}
