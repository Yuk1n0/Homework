package systemUI;

import java.awt.BorderLayout;
import java.awt.Choice;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import Users.Administrator;
import Users.User;

public class changeRoleUI extends JFrame implements ActionListener {

	private static final long serialVersionUID = 1L;

	private Administrator ad;
	private User user;
	private UserListUI last;
	private int row, col;

	private Font font;
	private Choice choice;
	private JButton yes;
	private JButton cancel;

	public changeRoleUI(Administrator ad, User user, UserListUI last, int row, int col) {
		this.row = row;
		this.col = col;
		this.ad = ad;
		this.user = user;
		this.last = last;

		font = new Font("宋体", Font.BOLD, 36);
		JLabel choose = new JLabel("修改用户权限",SwingUtilities.CENTER);
		choose.setFont(font);
		this.add(choose, BorderLayout.NORTH);

		font = new Font("宋体", Font.PLAIN, 24);
		choice = new Choice();
		choice.add("Administrator");
		choice.add("Operator");
		choice.add("Browser");
		choice.setFont(font);
		this.add(choice);

		yes = new JButton("确认");
		yes.setFont(font);
		yes.addActionListener(this);
		cancel = new JButton("取消");
		cancel.setFont(font);
		cancel.addActionListener(this);
		JPanel btn = new JPanel();
		btn.add(yes);
		btn.add(cancel);
		this.add(btn, BorderLayout.SOUTH);

		this.setTitle("修改权限");
		this.setSize(360, 200);
		this.setResizable(false);
		this.setVisible(true);
		this.setLocationRelativeTo(null);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == cancel) {
			this.dispose();
		}
		else if(e.getSource() == yes) {
			this.ad.changeRole(user, choice.getSelectedItem());
			JOptionPane.showMessageDialog(changeRoleUI.this, "修改权限成功！", "提示", JOptionPane.INFORMATION_MESSAGE);
			last.changedata( choice.getSelectedItem(), row, col);
			this.dispose();
		}
	}
}
