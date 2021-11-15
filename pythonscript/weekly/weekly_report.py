import re
import json
from jira import JIRA

def main():
    auth_data = {}
    with open('auth.json','r')as f:
        auth_data = json.load(f)
    print(auth_data)
    jira = JIRA("http://jira.i-tetris.com/", auth=(auth_data['username'], auth_data['password']))

    issues = jira.search_issues('resolved >= -1w AND assignee in (currentUser())', maxResults=-1)
    for issue in issues:
        jira_id = issue.key
        summary = issue.fields.summary
        status = issue.fields.status
        summary = re.sub(r'\[.*\]','', summary).strip()
        print(f"[Done][{jira_id}]{summary}")

    print('--------------------------')

    issues = jira.search_issues('status in ("In Progress") AND assignee in (currentUser())', maxResults=-1)
    for issue in issues:
        jira_id = issue.key
        summary = issue.fields.summary
        status = issue.fields.status
        summary = re.sub(r'\[.*\]','', summary).strip()
        print(f"[In-Progress][{jira_id}]{summary}")

    print('--------------------------')

    issues = jira.search_issues('status in ("TO DO", Reopened) AND assignee in (currentUser())', maxResults=-1)
    for issue in issues:
        jira_id = issue.key
        summary = issue.fields.summary
        status = issue.fields.status
        summary = re.sub(r'\[.*\]','', summary).strip()
        print(f"[ToDo][{jira_id}]{summary}")

if __name__ == '__main__':
    main()
